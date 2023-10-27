//
// Created by arden on 10/19/23.
//

#include "OscillatorCoefficients.h"

OscillatorCoefficients::OscillatorCoefficients() : samplerate(44100)
{

}

OscillatorCoefficients::~OscillatorCoefficients()
{

}

juce::Colour getBlurredPixel(juce::Image* im, float x, float y) {
    return im->getPixelAt((int)x, (int)y);
}

void OscillatorCoefficients::setFromCanvas (juce::Image* canvas, float proportion)
{
    auto order = 0;
    auto numSamples = 1;
    while (numSamples * 2 < canvas->getWidth() * 2) {
        numSamples *= 2;
        order++;
    }
    auto fft = juce::dsp::FFT(order);
    auto y = (canvas->getHeight() * proportion);
    auto samples = std::vector<float>();
    samples.resize(numSamples * 2);
    float summed = 0;
    for (int i = 0; i < numSamples; ++i) {
        auto x = (float)i * canvas->getWidth() / (float)numSamples;
        auto brightness = getBlurredPixel(canvas,x, y).getPerceivedBrightness();
        samples[i] = brightness * 2 - 1; // rescale from [0, 1] to [-1, 1]
        summed += samples[i];
    }
    float avg = summed / (float)numSamples;
    for (int i = 0; i < numSamples; ++i) {
        samples[i] -= avg; // get rid of DC offset
    }

    fft.performRealOnlyForwardTransform(&samples[0], true);
    // see juce docs: this interleaves the real and complex components.
    auto numCoefficients = numSamples / 2 + 1;
    magnitudes.resize(numCoefficients);
    phases.resize(numCoefficients);
    for (int i = 0; i < numCoefficients; ++i) {
        auto v = std::complex<float>(samples[i * 2], samples[i * 2 + 1]);
        magnitudes[i] = abs(v);
        magnitudes[i] /= samples.size();
        if ((0 < i) && (i < numCoefficients - 1)) {
            magnitudes[i] *= 2;
        }
        phases[i] = magnitudes[i] ? arg(v) : 0;
    }
}

void OscillatorCoefficients::setSampleRate (float fs)
{
    samplerate = fs;
}


float OscillatorCoefficients::getMagnitude (float basefreq, int harmonic)
{
    auto maxHarmonic = getMaxHarmonic(basefreq);
    if (harmonic < maxHarmonic) {
        return magnitudes[harmonic];
    } else {
        return 0;
    }
}

float OscillatorCoefficients::getPhase (float basefreq, int harmonic)
{
    auto maxHarmonic = getMaxHarmonic(basefreq);
    if (harmonic < maxHarmonic) {
        return phases[harmonic];
    } else {
        return 0;
    }
}

int OscillatorCoefficients::getMaxHarmonic(float basefreq)
{
    auto maxFreq = samplerate * 0.5 * 0.95;
    return std::min((int)magnitudes.size() - 1, (int)(maxFreq / basefreq));
}

int OscillatorCoefficients::getNumCoefficients()
{
    return magnitudes.size();
}
