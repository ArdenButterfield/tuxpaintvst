//
// Created by arden on 10/23/23.
//

#include "OscilloscopeData.h"
#include "juce_core/juce_core.h"
#include <iostream>

OscilloscopeData::OscilloscopeData()
{
    period = 100;
    samples.resize(period, 0);
    position = 0;
    freshSamplesNeeded = samples.size();
}

OscilloscopeData::~OscilloscopeData()
{

}

void OscilloscopeData::resize (float _period)
{
    if (!juce::approximatelyEqual(period, _period)) {
        period = _period;
        samples.resize((int)period, 0);
        position = 0;
        freshSamplesNeeded = samples.size();
    }
}

void OscilloscopeData::insertSamples (const float* newSamples, int numSamples)
{
    if (freshSamplesNeeded) {
        int i = 0;
        for (; (i < numSamples) && freshSamplesNeeded; ++i) {
            samples[(int)position] = newSamples[i];
            --freshSamplesNeeded;
            position += 1;
            while (position >= period) {
                position -= period;
            }
        }
        for (; i < numSamples; ++i) {
            position += 1;
            while (position >= period) {
                position -= period;
            }
        }
    } else {
        position += (float)numSamples;
        while (position >= period) {
            position -= period;
        }
    }

}

std::vector<float>* OscilloscopeData::getSamples()
{
    freshSamplesNeeded = samples.size();
    return &samples;
}

