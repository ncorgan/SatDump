#pragma once

#include <uhd/device.hpp>
#include <uhd/usrp/multi_usrp.hpp>

#include <functional>

class UsrpBase
{
protected:
    UsrpBase(const std::string &args);
    virtual ~UsrpBase();

    uhd::usrp::multi_usrp::sptr usrp;

    size_t channel = 0;

    template <typename T>
    static std::vector<T> getAvailableDevices()
    {
        std::vector<T> results;
        for(const auto &device: uhd::device::find(uhd::device_addr_t("")))
        {
            results.emplace_back(T{
                "uhd",
                device.to_pp_string(),
                std::hash<std::string>()(device.to_string()),
            });
        }

        return results;
    }

};
