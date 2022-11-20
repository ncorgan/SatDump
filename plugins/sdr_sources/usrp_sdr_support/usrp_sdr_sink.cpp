#include "usrp_sdr_sink.h"

UsrpSink::UsrpSink(dsp::SinkDescriptor sink) :
    DSPSampleSink(sink),
    UsrpBase(sink.name)
{
}

UsrpSink::~UsrpSink()
{
}

void UsrpSink::set_settings(nlohmann::json settings)
{
    (void)settings;
}

nlohmann::json UsrpSink::get_settings()
{
    return {};
}

void UsrpSink::open()
{
}

void UsrpSink::start(std::shared_ptr<dsp::stream<complex_t>> stream)
{
    (void)stream;
}

void UsrpSink::stop()
{
}

void UsrpSink::close()
{
}

void UsrpSink::set_frequency(uint64_t frequency)
{
    (void)frequency;
}

void UsrpSink::drawControlUI()
{
}

void UsrpSink::set_samplerate(uint64_t samplerate)
{
    (void)samplerate;
}

uint64_t UsrpSink::get_samplerate()
{
    return 0;
}
