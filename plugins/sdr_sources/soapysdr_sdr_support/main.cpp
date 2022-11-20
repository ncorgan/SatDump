#include "core/plugin.h"
#include "logger.h"
#include "soapysdr_sdr_source.h"
#include "soapysdr_sdr_sink.h"

#include <SoapySDR/Logger.hpp>

static void satdump_loghandler(const SoapySDR::LogLevel level, const char *message)
{
    auto spdlog_level = spdlog::level::info;

    switch(level)
    {
    case SOAPY_SDR_FATAL:
    case SOAPY_SDR_CRITICAL:
        spdlog_level = spdlog::level::critical;
        break;

    case SOAPY_SDR_ERROR:
        spdlog_level = spdlog::level::err;
        break;

    case SOAPY_SDR_WARNING:
        spdlog_level = spdlog::level::warn;
        break;

    case SOAPY_SDR_NOTICE:
    case SOAPY_SDR_INFO:
        spdlog_level = spdlog::level::info;
        break;

    case SOAPY_SDR_DEBUG:
        spdlog_level = spdlog::level::debug;
        break;

    default:
        spdlog_level = spdlog::level::trace;
        break;
    }

    logger->log(spdlog_level, "SoapySDR: {}", message);
}

class SoapySdrSDRSupport : public satdump::Plugin
{
public:
    std::string getID()
    {
        return "soapysdr_sdr_support";
    }

    void init()
    {
        satdump::eventBus->register_handler<dsp::RegisterDSPSampleSourcesEvent>(registerSources);
        satdump::eventBus->register_handler<dsp::RegisterDSPSampleSinksEvent>(registerSinks);

        // Redirect SoapySDR's logging into SatDump's infrastructure. Pass all messages through
        // and let SatDump decide what goes through.
        SoapySDR::registerLogHandler(satdump_loghandler);
        SoapySDR::setLogLevel(SOAPY_SDR_SSI);
    }

    static void registerSources(const dsp::RegisterDSPSampleSourcesEvent &evt)
    {
        evt.dsp_sources_registry.insert({SoapySdrSource::getID(), {SoapySdrSource::getInstance, SoapySdrSource::getAvailableSources}});
    }

    static void registerSinks(const dsp::RegisterDSPSampleSinksEvent &evt)
    {
        evt.dsp_sinks_registry.insert({SoapySdrSink::getID(), {SoapySdrSink::getInstance, SoapySdrSink::getAvailableSinks}});
    }
};

PLUGIN_LOADER(SoapySdrSDRSupport)
