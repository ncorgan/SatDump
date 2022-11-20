#include "soapysdr_sdr_sink.h"

SoapySdrSink::SoapySdrSink(dsp::SinkDescriptor sink) : DSPSampleSink(sink)
{
}

SoapySdrSink::~SoapySdrSink()
{
}

void SoapySdrSink::set_settings(nlohmann::json settings)
{
    (void)settings;
}

nlohmann::json SoapySdrSink::get_settings()
{
    return {};
}

void SoapySdrSink::open()
{
}

void SoapySdrSink::start(std::shared_ptr<dsp::stream<complex_t>> stream)
{
    (void)stream;
}

void SoapySdrSink::stop()
{
}

void SoapySdrSink::close()
{
}

void SoapySdrSink::set_frequency(uint64_t frequency)
{
    (void)frequency;
}

void SoapySdrSink::drawControlUI()
{
}

void SoapySdrSink::set_samplerate(uint64_t samplerate)
{
    (void)samplerate;
}

uint64_t get_samplerate()
{
    return 0;
}
