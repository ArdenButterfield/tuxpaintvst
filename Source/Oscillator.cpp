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
    x = magnitude * cos(startingPhase);
    y = magnitude * sin(startingPhase);
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
    m00 = cos(angleIncrement);
    m01 = -sin(angleIncrement);
    m10 = sin(angleIncrement);
    m11 = cos(angleIncrement);
}
