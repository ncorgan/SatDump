#pragma once

#include <nlohmann/json.hpp>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>

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
};
