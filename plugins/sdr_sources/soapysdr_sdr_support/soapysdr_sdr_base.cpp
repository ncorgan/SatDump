#include "soapysdr_sdr_base.h"

SoapySdrBase::SoapySdrBase(const std::string &args):
    device(SoapySDR::Device::make(args))
{
}

SoapySdrBase::~SoapySdrBase()
{
    if(device) SoapySDR::Device::unmake(device);
}

// TODO: add gain, bandwidth, other Soapy API
nlohmann::json SoapySdrBase::get_and_convert_settings() const
{
    return {};
}

// TODO: add gain, bandwidth, other Soapy API
void SoapySdrBase::convert_and_set_settings(const nlohmann::json &settings)
{
    (void)settings;
}
