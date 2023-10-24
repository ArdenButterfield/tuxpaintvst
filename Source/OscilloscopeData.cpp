//
// Created by arden on 10/23/23.
//

#include "OscilloscopeData.h"

OscilloscopeData::OscilloscopeData()
{
    samples.resize(100, 0);
    position = 0;
}

OscilloscopeData::~OscilloscopeData()
{

}

void OscilloscopeData::resize (int period)
{
    samples.resize(period, 0);
    position = 0;
}

void OscilloscopeData::insertSamples (const float* newSamples, int numSamples)
{
    for (int i = 0; i < numSamples; ++i) {
        samples[position] = newSamples[i];
        position++;
        position %= samples.size();
    }
}

const std::vector<float>* const OscilloscopeData::getSamples() const
{
    return &samples;
}

