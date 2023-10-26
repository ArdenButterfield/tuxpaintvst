//
// Created by arden on 10/19/23.
//

#ifndef TUXPAINTVST_OSCILLATORCOEFFICIENTS_H
#define TUXPAINTVST_OSCILLATORCOEFFICIENTS_H

#include "juce_graphics/juce_graphics.h"
#include "juce_dsp/juce_dsp.h"
#include <cmath>
#include <complex>

class OscillatorCoefficients
{
public:
    OscillatorCoefficients();
    ~OscillatorCoefficients();
    void setFromCanvas(juce::Image* canvas, float proportion);
    void setSampleRate(float fs);
    float getMagnitude(float baseFreq, int harmonic);
    float getPhase(float baseFreq, int harmonic);
    int getMaxHarmonic(float baseFreq);
    int getNumCoefficients();
private:
    std::vector<float> magnitudes;
    std::vector<float> phases;
    float samplerate;
};

#endif //TUXPAINTVST_OSCILLATORCOEFFICIENTS_H
