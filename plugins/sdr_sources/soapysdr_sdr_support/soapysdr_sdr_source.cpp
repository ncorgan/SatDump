#include "soapysdr_sdr_source.h"

SoapySdrSource::SoapySdrSource(dsp::SourceDescriptor source) :
    DSPSampleSource(source),
    SoapySdrBase(source.name, SOAPY_SDR_RX)
{
}

SoapySdrSource::~SoapySdrSource()
{
    stop();
    close();
}

void SoapySdrSource::set_settings(nlohmann::json settings)
{
    SoapySdrBase::convert_and_set_settings(settings);
}

nlohmann::json SoapySdrSource::get_settings()
{
    return SoapySdrBase::get_and_convert_settings();
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

void SoapySdrSource::drawControlUI()
{
}

void SoapySdrSource::set_frequency(uint64_t frequency)
{
    device->setFrequency(direction, channel, double(frequency));

    d_frequency = uint64_t(device->getFrequency(direction, channel));
}

void SoapySdrSource::set_samplerate(uint64_t samplerate)
{
    device->setSampleRate(direction, channel, double(samplerate));
}

uint64_t SoapySdrSource::get_samplerate()
{
    return uint64_t(device->getSampleRate(direction, channel));
}
