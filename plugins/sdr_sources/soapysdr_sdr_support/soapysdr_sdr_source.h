#pragma once

#include "soapysdr_sdr_base.h"

#include "common/dsp_source_sink/dsp_sample_source.h"

#include <atomic>
#include <memory>
#include <thread>

class SoapySdrSource : public dsp::DSPSampleSource, public SoapySdrBase
{
public:
    //
    // Methods
    //

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

    void work_thread_fcn_CF32();
    void work_thread_fcn_CS16();

    //
    // SatDump infrastructure
    //

    static std::string getID() { return "soapysdr"; }
    static std::shared_ptr<dsp::DSPSampleSource> getInstance(dsp::SourceDescriptor source) { return std::make_shared<SoapySdrSource>(source); }

    static inline std::vector<dsp::SourceDescriptor> getAvailableSources()
    {
        return SoapySdrBase::getAvailableDevices<dsp::SourceDescriptor>();
    }

    //
    // Members
    //

    std::atomic_bool is_open{false};
    std::atomic_bool run_thread{false};
    std::unique_ptr<std::thread> work_thread{nullptr};
};
