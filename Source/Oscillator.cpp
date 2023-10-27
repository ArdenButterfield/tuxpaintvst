//
// Created by arden on 10/18/23.
//

#include <iostream>

#include "Oscillator.h"

Oscillator::Oscillator()
{
    frequency = 0;
    startingPhase = 0;
    magnitude = 0;
    fs = 44100;

    updateMatrix();
}

void Oscillator::setSamplerate (float rate)
{
    fs = rate;
    updateMatrix();
}

void Oscillator::setFrequency (float freq)
{
    frequency = freq;
    updateMatrix();
}

void Oscillator::setMagnitude (float mag)
{
    magnitude = mag;
    updateMatrix();
}

void Oscillator::setStartingPhase (float phase)
{
    startingPhase = phase;
    updateMatrix();
}

void Oscillator::reset()
{
    x = magnitude * cosf(startingPhase);
    y = magnitude * sinf(startingPhase);
}

void Oscillator::processBlock (float* samples, int numSamples)
{
    float newx, newy;
    for (auto i = 0; i < numSamples; ++i) {
        newx = x * m00 + y * m01;
        newy = x * m10 + y * m11;
        samples[i] += newx;

        x = newx;
        y = newy;
    }
}

void Oscillator::updateMatrix()
{
    auto angleIncrement = frequency * twoPi / fs;
    m00 = cosf(angleIncrement);
    m01 = -sinf(angleIncrement);
    m10 = sinf(angleIncrement);
    m11 = cosf(angleIncrement);
}

void Oscillator::changeMidStream (float mag, float phase)
{
    if ((mag == magnitude) && (phase == startingPhase)) {
        return;
    }
    float newx, newy;
    if ((magnitude == 0) && (mag != 0)) {
        newx = mag * cosf(phase);
        newy = mag * sinf(phase);
    } else {
        auto rotation = phase - startingPhase;
        auto scale = mag / magnitude;

        auto xscale = x * scale;
        auto yscale = y * scale;

        newx = xscale * cosf(rotation) - yscale * sinf(rotation);
        newy = xscale * sinf(rotation) + yscale * cosf(rotation);
    }

    magnitude = mag;
    startingPhase = phase;

    // TODO: change gradually
    x = newx;
    y = newy;
}
