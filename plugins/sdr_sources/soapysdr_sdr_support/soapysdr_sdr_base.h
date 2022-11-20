#pragma once

#include <nlohmann/json.hpp>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>

class SoapySdrBase
{
protected:
    SoapySdrBase(const std::string &args);
    virtual ~SoapySdrBase();

    SoapySDR::Device *device = nullptr;

    nlohmann::json get_and_convert_settings() const;

    void convert_and_set_settings(const nlohmann::json &settings);
};
