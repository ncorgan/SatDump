#include "core/plugin.h"
#include "logger.h"
#include "soapysdr_sdr_source.h"
#include "soapysdr_sdr_sink.h"

#include <SoapySDR/Logger.hpp>

// Redirect SoapySDR's logging into SatDump's infrastructure.
static void satdump_loghandler(const SoapySDR::LogLevel level, const char* message)
{
    (void)level;
    (void)message;
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

        SoapySDR::registerLogHandler(satdump_loghandler);
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
