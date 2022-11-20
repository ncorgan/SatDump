#pragma once

#include "soapysdr_sdr_base.h"

#include "common/dsp_source_sink/dsp_sample_source.h"

class SoapySdrSource : public dsp::DSPSampleSource, public SoapySdrBase
{
public:
    SoapySdrSource(dsp::SourceDescriptor source);
    virtual ~SoapySdrSource();

    void set_settings(nlohmann::json settings);
    nlohmann::json get_settings();

    void open();
    void start();
    void stop();
    void close();

    void set_frequency(uint64_t frequency);

    void drawControlUI();

    void set_samplerate(uint64_t samplerate);
    uint64_t get_samplerate();

    static std::string getID() { return "soapysdr"; }
    static std::shared_ptr<dsp::DSPSampleSource> getInstance(dsp::SourceDescriptor source) { return std::make_shared<SoapySdrSource>(source); }
    static std::vector<dsp::SourceDescriptor> getAvailableSources();
};
