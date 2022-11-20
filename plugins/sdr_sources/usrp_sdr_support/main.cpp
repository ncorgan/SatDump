#include "core/plugin.h"
#include "logger.h"
#include "usrp_sdr_source.h"
#include "usrp_sdr_sink.h"

#include <uhd/utils/log_add.hpp>

// See: https://github.com/pothosware/SoapyUHD/blob/master/SoapyUHDDevice.cpp
static void satdump_log(const uhd::log::logging_info &info)
{
    // Build a log message formatted from the information
    std::string message;

    if (not info.file.empty())
    {
        std::string shortfile = info.file.substr(info.file.find_last_of("/\\") + 1);
        message += "[" + shortfile + ":" + std::to_string(info.line) + "] ";
    }

    if (not info.component.empty())
    {
        message += "[" + info.component + "] ";
    }

    message += info.message;

    auto spdlog_level = spdlog::level::info;

    switch(info.verbosity)
    {
    case uhd::log::trace:   spdlog_level = spdlog::level::trace; break;
    case uhd::log::debug:   spdlog_level = spdlog::level::debug; break;
    case uhd::log::info:    spdlog_level = spdlog::level::info; break;
    case uhd::log::warning: spdlog_level = spdlog::level::warn; break;
    case uhd::log::error:   spdlog_level = spdlog::level::err; break;
    case uhd::log::fatal:   spdlog_level = spdlog::level::critical; break;
    default: break;
    }

    logger->log(spdlog_level, "UHD: {}", message);
}

class UsrpSDRSupport : public satdump::Plugin
{
public:
    std::string getID()
    {
        return "usrp_sdr_support";
    }

    void init()
    {
        satdump::eventBus->register_handler<dsp::RegisterDSPSampleSourcesEvent>(registerSources);
        satdump::eventBus->register_handler<dsp::RegisterDSPSampleSinksEvent>(registerSinks);

        // Add SatDump's logging infrastructure as a UHD log handler. Pass all messages through
        // and let SatDump decide what goes through.
        uhd::log::add_logger("SatDump", satdump_log);
        uhd::log::set_log_level(uhd::log::trace);
    }

    static void registerSources(const dsp::RegisterDSPSampleSourcesEvent &evt)
    {
        evt.dsp_sources_registry.insert({UsrpSource::getID(), {UsrpSource::getInstance, UsrpSource::getAvailableSources}});
    }

    static void registerSinks(const dsp::RegisterDSPSampleSinksEvent &evt)
    {
        evt.dsp_sinks_registry.insert({UsrpSink::getID(), {UsrpSink::getInstance, UsrpSink::getAvailableSinks}});
    }
};

PLUGIN_LOADER(UsrpSDRSupport)
