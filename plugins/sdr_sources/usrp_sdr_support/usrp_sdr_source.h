#pragma once

#include "common/dsp_source_sink/dsp_sample_source.h"

class UsrpSource : public dsp::DSPSampleSource
{
public:
    UsrpSource(dsp::SourceDescriptor source);
    virtual ~UsrpSource();

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

    static std::string getID() { return "usrp"; }
    static std::shared_ptr<dsp::DSPSampleSource> getInstance(dsp::SourceDescriptor source) { return std::make_shared<UsrpSource>(source); }
    static std::vector<dsp::SourceDescriptor> getAvailableSources();
};
