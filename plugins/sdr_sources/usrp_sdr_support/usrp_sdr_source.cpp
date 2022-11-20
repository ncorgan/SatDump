#include "usrp_sdr_source.h"

UsrpSource::UsrpSource(dsp::SourceDescriptor source) :
    DSPSampleSource(source),
    UsrpBase(source.name)
{
}

UsrpSource::~UsrpSource()
{
    stop();
    close();
}

void UsrpSource::set_settings(nlohmann::json settings)
{
    (void)settings;
}

nlohmann::json UsrpSource::get_settings()
{
    return {};
}

void UsrpSource::open()
{
}

void UsrpSource::start()
{
}

void UsrpSource::stop()
{
}

void UsrpSource::close()
{
}

void UsrpSource::set_frequency(uint64_t frequency)
{
    (void)frequency;
}

void UsrpSource::drawControlUI()
{
}

void UsrpSource::set_samplerate(uint64_t samplerate)
{
    (void)samplerate;
}

uint64_t UsrpSource::get_samplerate()
{
    return {};
}
