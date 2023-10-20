//
// Created by arden on 10/18/23.
//

#ifndef TUXPAINTVST_OSCILLATOR_H
#define TUXPAINTVST_OSCILLATOR_H

#include <cmath>

class Oscillator
{
public:
    Oscillator();
    void setSamplerate(float rate);
    void setFrequency(float freq);
    void setStartingPhase(float phase);
    void setMagnitude(float mag);
    void reset();
    void processBlock(float* samples, int numSamples);
    const float twoPi = 2 * 3.141592653589793238;
    float fs;

    float frequency;
    float startingPhase;
    float magnitude;

    float x;
    float y;

    float m00, m01, m10, m11;

    void updateMatrix();
};

#endif //TUXPAINTVST_OSCILLATOR_H
