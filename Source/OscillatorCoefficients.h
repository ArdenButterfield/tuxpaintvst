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
    void setBaseFreq(float f);
    float getMagnitude(int harmonic);
    float getPhase(int harmonic);
    int getMaxHarmonic();
    int getNumCoefficients();
private:
    std::vector<float> magnitudes;
    std::vector<float> phases;
    float samplerate;
    float basefreq;
    int maxHarmonic;
};

#endif //TUXPAINTVST_OSCILLATORCOEFFICIENTS_H
