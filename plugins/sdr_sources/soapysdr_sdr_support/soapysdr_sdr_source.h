#pragma once

#include "soapysdr_sdr_base.h"

#include "common/dsp_source_sink/dsp_sample_source.h"

class SoapySdrSource : public dsp::DSPSampleSource, public SoapySdrBase
{
public:
    SoapySdrSource(dsp::SourceDescriptor source);

    // TODO: with parent's non-virtual dtor, figure out how this works
    virtual ~SoapySdrSource();

    void set_settings(nlohmann::json settings) override;
    nlohmann::json get_settings() override;

    void open() override;
    void start() override;
    void stop() override;
    void close() override;

    void drawControlUI() override;

    void set_frequency(uint64_t frequency) override;

    void set_samplerate(uint64_t samplerate);
    uint64_t get_samplerate();

    static std::string getID() { return "soapysdr"; }
    static std::shared_ptr<dsp::DSPSampleSource> getInstance(dsp::SourceDescriptor source) { return std::make_shared<SoapySdrSource>(source); }

    static inline std::vector<dsp::SourceDescriptor> getAvailableSources()
    {
        return SoapySdrBase::getAvailableDevices<dsp::SourceDescriptor>();
    }
};
