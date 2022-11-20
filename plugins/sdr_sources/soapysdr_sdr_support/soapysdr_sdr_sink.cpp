#include "soapysdr_sdr_sink.h"

SoapySdrSink::SoapySdrSink(dsp::SinkDescriptor sink) :
    DSPSampleSink(sink),
    SoapySdrBase(sink.name, SOAPY_SDR_TX)
{
}

SoapySdrSink::~SoapySdrSink()
{
}

void SoapySdrSink::set_settings(nlohmann::json settings)
{
    SoapySdrBase::convert_and_set_settings(settings);
}

nlohmann::json SoapySdrSink::get_settings()
{
    return SoapySdrBase::get_and_convert_settings();
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
