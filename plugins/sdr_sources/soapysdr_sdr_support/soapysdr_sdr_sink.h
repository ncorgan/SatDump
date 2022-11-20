#pragma once

#include "soapysdr_sdr_base.h"

#include "common/dsp_source_sink/dsp_sample_sink.h"

class SoapySdrSink : public dsp::DSPSampleSink, public SoapySdrBase
{
public:
    SoapySdrSink(dsp::SinkDescriptor sink);
    virtual ~SoapySdrSink();

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

    static std::string getID() { return "soapysdr"; }
    static std::shared_ptr<dsp::DSPSampleSink> getInstance(dsp::SinkDescriptor sink) { return std::make_shared<SoapySdrSink>(sink); }
    static std::vector<dsp::SinkDescriptor> getAvailableSinks();
};
