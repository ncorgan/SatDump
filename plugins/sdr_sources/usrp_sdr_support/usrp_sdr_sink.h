#pragma once

#include "usrp_sdr_base.h"

#include "common/dsp_source_sink/dsp_sample_sink.h"

class UsrpSink : public dsp::DSPSampleSink, public UsrpBase
{
public:
    UsrpSink(dsp::SinkDescriptor sink);
    virtual ~UsrpSink();

    void set_settings(nlohmann::json settings) override;
    nlohmann::json get_settings() override;

    void open() override;
    void start(std::shared_ptr<dsp::stream<complex_t>> stream) override;
    void stop() override;
    void close() override;

    void set_frequency(uint64_t frequency) override;

    void drawControlUI() override;

    void set_samplerate(uint64_t samplerate) override;
    uint64_t get_samplerate() override;

    static std::string getID() { return "usrp"; }
    static std::shared_ptr<dsp::DSPSampleSink> getInstance(dsp::SinkDescriptor sink) { return std::make_shared<UsrpSink>(sink); }

    static inline std::vector<dsp::SinkDescriptor> getAvailableSinks()
    {
        return UsrpBase::getAvailableDevices<dsp::SinkDescriptor>();
    }
};
