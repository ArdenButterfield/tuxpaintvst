//
// Created by arden on 10/16/23.
//

#ifndef TUXPAINTVST_TUXSYNTHVOICE_H
#define TUXPAINTVST_TUXSYNTHVOICE_H

#include <juce_audio_basics/juce_audio_basics.h>

#include "Oscillator.h"
#include "OscillatorCoefficients.h"

class TuxSynthVoice : public juce::SynthesiserVoice
{
public:
    TuxSynthVoice(OscillatorCoefficients* c);
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved (int) override;
    void controllerMoved (int, int) override;
    void renderNextBlock (juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
    void setCurrentPlaybackSampleRate(double newRate) override;
    void updateWavetable();
private:
    std::vector<Oscillator> oscillators;
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
    bool noteOn;
    OscillatorCoefficients* coefficients;
    int maxHarmonic;
};

#endif //TUXPAINTVST_TUXSYNTHVOICE_H
