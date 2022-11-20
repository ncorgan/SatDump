#pragma once

#include <nlohmann/json.hpp>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>

#include <functional>
#include <vector>

class SoapySdrBase
{
protected:
    SoapySdrBase(const std::string &args, const int direction);
    virtual ~SoapySdrBase();

    // TODO: channel?
    SoapySDR::Device *device = nullptr;
    const int direction = -1;
    size_t channel = 0;

    nlohmann::json get_and_convert_settings() const;

    void convert_and_set_settings(const nlohmann::json &settings);

    template <typename T>
    static std::vector<T> getAvailableDevices()
    {
        // TODO: replace KwargsToString to look more like uhd::device_addr_t::to_pp_string
        std::vector<T> results;
        for(const auto &device: SoapySDR::Device::enumerate())
        {
            results.emplace_back(T{
                "soapysdr",
                SoapySDR::KwargsToString(device),
                std::hash<std::string>()(SoapySDR::KwargsToString(device))
            });
        }

        return results;
    }
};
