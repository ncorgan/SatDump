#include "soapysdr_sdr_base.h"

#include "logger.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>

SoapySdrBase::SoapySdrBase(const std::string &args, const int direction):
    device(SoapySDR::Device::make(args)),
    direction(direction)
{
    // We control this, so if this fails, it's on us.
    assert((direction == SOAPY_SDR_TX) or (direction == SOAPY_SDR_RX));
}

SoapySdrBase::~SoapySdrBase()
{
    if(device) SoapySDR::Device::unmake(device);
}

nlohmann::json SoapySdrBase::get_and_convert_settings() const
{
    nlohmann::json json_settings;
    for(const auto &info: device->getSettingInfo())
    {
        switch(info.type)
        {
        case SoapySDR::ArgInfo::BOOL:
            json_settings[info.key] = device->readSetting<bool>(info.key);
            break;

        case SoapySDR::ArgInfo::INT:
            try
            {
                json_settings[info.key] = device->readSetting<ssize_t>(info.key);
            }
            catch(const std::out_of_range &)
            {
                json_settings[info.key] = device->readSetting<size_t>(info.key);
            }
            break;

        case SoapySDR::ArgInfo::FLOAT:
            json_settings[info.key] = device->readSetting<double>(info.key);
            break;

        default:
            json_settings[info.key] = device->readSetting(info.key);
            break;
        }
    }

    // Other SoapySDR API (TODO: others worth it?)
    json_settings["gain"] = device->getGain(direction, channel);
    json_settings["bandwidth"] = device->getBandwidth(direction, channel);

    return json_settings;
}

void SoapySdrBase::convert_and_set_settings(const nlohmann::json &settings)
{
    const auto setting_infos = device->getSettingInfo();

    for(const auto &[key, val]: settings.items())
    {
        // Is this a Soapy Setting? If not, check the settings we use for
        // SoapySDR API functions.
        auto iter = std::find_if(
            setting_infos.begin(),
            setting_infos.end(),
            [&key](const SoapySDR::ArgInfo &setting_info)
            {
                return (setting_info.key == key);
            });
        if(iter != setting_infos.end())
        {
            switch(val.type())
            {
            case nlohmann::json::value_t::boolean:
                device->writeSetting<bool>(key, val.get<bool>());
                break;

            case nlohmann::json::value_t::string:
                device->writeSetting<std::string>(key, val.get<std::string>());
                break;

            case nlohmann::json::value_t::number_integer:
                device->writeSetting<ssize_t>(key, val.get<ssize_t>());
                break;

            case nlohmann::json::value_t::number_unsigned:
                device->writeSetting<size_t>(key, val.get<size_t>());
                break;

            case nlohmann::json::value_t::number_float:
                device->writeSetting<double>(key, val.get<double>());
                break;

            default:
                logger->error("JSON type {} not supported for SoapySDR settings. Ignoring.", val.type_name());
                break;
            }
        }
        else if(key == "gain")
        {
            device->setGain(direction, channel, val.get<double>());
        }
        else if(key == "bandwidth")
        {
            device->setBandwidth(direction, channel, val.get<double>());
        }
    }
}
