#include "soapysdr_sdr_source.h"

#include <volk/volk.h>

#include <cassert>

SoapySdrSource::SoapySdrSource(dsp::SourceDescriptor source) :
    DSPSampleSource(source),
    SoapySdrBase(source.name, SOAPY_SDR_RX)
{
}

SoapySdrSource::~SoapySdrSource()
{
    stop();
    close();
}

void SoapySdrSource::set_settings(nlohmann::json settings)
{
    SoapySdrBase::convert_and_set_settings(settings);
}

nlohmann::json SoapySdrSource::get_settings()
{
    return SoapySdrBase::get_and_convert_settings();
}

void SoapySdrSource::open()
{
    stream = device->setupStream(
        direction,
        format,
        std::vector<size_t>{channel},
        tune_args);
    mtu = device->getStreamMTU(stream);

    is_open = true;
}

// TODO: include tune args in settings?
void SoapySdrSource::start()
{
    // TODO: if CF32 not supported, CS16
    work_thread.reset(new std::thread(&SoapySdrSource::work_thread_fcn_CF32, this));
}

void SoapySdrSource::stop()
{
    assert(device);
    assert(stream);

    work_thread->join();
    work_thread.reset();

    device->deactivateStream(stream);
}

void SoapySdrSource::close()
{
    assert(device);
    assert(stream);

    device->closeStream(stream);
    stream = nullptr;

    is_open = false;
}

void SoapySdrSource::drawControlUI()
{
}

void SoapySdrSource::set_frequency(uint64_t frequency)
{
    assert(device);

    device->setFrequency(direction, channel, double(frequency));

    d_frequency = uint64_t(device->getFrequency(direction, channel));
}

void SoapySdrSource::set_samplerate(uint64_t samplerate)
{
    assert(device);

    device->setSampleRate(direction, channel, double(samplerate));
}

uint64_t SoapySdrSource::get_samplerate()
{
    assert(device);

    return uint64_t(device->getSampleRate(direction, channel));
}

void SoapySdrSource::work_thread_fcn_CF32()
{
    while(run_thread)
    {
        assert(device);
        assert(stream);

        // TODO: can this go outside while loop to avoid allocations?
        std::vector<void *> buffs{&output_stream->writeBuf};

        // TODO: args if we store them
        int flags = 0;
        long long timeNs = 0;
        auto streamRet = device->readStream(
            stream,
            buffs.data(),
            mtu,
            flags,
            timeNs);
        if(streamRet > 0)
        {
            output_stream->swap(streamRet);
            // What's SatDump's policy when this fails?
        }
        // else what's SatDump's policy for errors here?
    }
}

void SoapySdrSource::work_thread_fcn_CS16()
{
    assert(mtu > 0);

    std::vector<lv_16sc_t> intermediate_vec(mtu);
    auto *intermediate = intermediate_vec.data();

    while(run_thread)
    {
        assert(device);
        assert(stream);

        // TODO: args if we store them
        int flags = 0;
        long long timeNs = 0;
        auto streamRet = device->readStream(
            stream,
            (void **)&intermediate,
            mtu,
            flags,
            timeNs);
        if(streamRet > 0)
        {
            static_assert(sizeof(lv_32fc_t) == sizeof(complex_t));

            volk_16ic_convert_32fc((lv_32fc_t *)output_stream->writeBuf, intermediate, streamRet);
            output_stream->swap(streamRet);
            // What's SatDump's policy when this fails?
        }
        // else what's SatDump's policy for errors here?
    }
}
