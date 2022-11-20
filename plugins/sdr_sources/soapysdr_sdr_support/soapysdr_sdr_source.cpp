#include "soapysdr_sdr_source.h"

SoapySdrSource::SoapySdrSource(dsp::SourceDescriptor source) : DSPSampleSource(source)
{
}

SoapySdrSource::~SoapySdrSource()
{
    stop();
    close();
}

void SoapySdrSource::set_settings(nlohmann::json settings)
{
    (void)settings;
}

nlohmann::json SoapySdrSource::get_settings()
{
    return {};
}

void SoapySdrSource::open()
{
}

void SoapySdrSource::start()
{
}

void SoapySdrSource::stop()
{
}

void SoapySdrSource::close()
{
}

void SoapySdrSource::set_frequency(uint64_t frequency)
{
    (void)frequency;
}

void SoapySdrSource::drawControlUI()
{
}

void SoapySdrSource::set_samplerate(uint64_t samplerate)
{
    (void)samplerate;
}

uint64_t SoapySdrSource::get_samplerate()
{
    return {};
}

std::vector<dsp::SourceDescriptor> SoapySdrSource::getAvailableSources()
{
    return {};
}
