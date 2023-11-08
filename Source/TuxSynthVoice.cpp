//
// Created by arden on 10/16/23.
//

#include "TuxSynthVoice.h"
#include "TuxSynthSound.h"

TuxSynthVoice::TuxSynthVoice(OscillatorCoefficients* c) : coefficients(c)
{
    maxHarmonic = 0;
    noteOn = false;
    adsr.setSampleRate(getSampleRate());
    adsr.setParameters({0.0,1.0,0.0,1.0});
}

bool TuxSynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<TuxSynthSound*> (sound) != nullptr;
}

void TuxSynthVoice::updateWavetable()
{
    auto midiNoteNumber = getCurrentlyPlayingNote();
    if (midiNoteNumber >= 0) {
        auto cyclesPerSecond = (float)juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        maxHarmonic = coefficients->getMaxHarmonic(cyclesPerSecond);
        for (int i = 0; i < maxHarmonic; ++i) {
            auto mag = coefficients->getMagnitude(cyclesPerSecond, i);
            auto phase = coefficients->getPhase(cyclesPerSecond,i);
            oscillators[i].changeMidStream(mag, phase);
        }
    }
}

void TuxSynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    adsr.reset();
    adsr.noteOn();
    oscillators.resize(coefficients->getNumCoefficients());
    noteOn = true;
    tailOff = 0.0;
    auto cyclesPerSecond = (float)juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    maxHarmonic = coefficients->getMaxHarmonic(cyclesPerSecond);
    for (int i = 0; i < maxHarmonic; ++i) {
        oscillators[i].setSamplerate((float)getSampleRate());
        oscillators[i].setFrequency(cyclesPerSecond * (float)i);
        oscillators[i].setMagnitude(coefficients->getMagnitude(cyclesPerSecond, i) * velocity);
        oscillators[i].setStartingPhase(coefficients->getPhase(cyclesPerSecond, i));
        oscillators[i].reset();
    }
}

void TuxSynthVoice::stopNote (float, bool allowTailOff)
{
    noteOn = false;
    adsr.noteOff();
    if (allowTailOff)
    {
        clearCurrentNote();
    }
    else
    {
        clearCurrentNote();
    }

}

void TuxSynthVoice::pitchWheelMoved (int)
{

}

void TuxSynthVoice::controllerMoved (int, int)
{

}

void TuxSynthVoice::renderNextBlock (juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    {
        if (noteOn) // [7]
        {
            auto samples = juce::AudioSampleBuffer(1, numSamples);
            samples.clear();
            for (int i = 0; i < maxHarmonic; ++i) {
                // oscillators[i].processBlock(outputBuffer.getWritePointer(0,startSample), numSamples);
                oscillators[i].processBlock(samples.getWritePointer(0,0), numSamples);
            }
            adsr.applyEnvelopeToBuffer(samples,0,numSamples);
            outputBuffer.addFrom(0,startSample,samples,0,0,numSamples,1);
        }
        else
        {
/*
            while (--numSamples >= 0) // [6]
            {
                auto currentSample = (float) (std::sin (currentAngle) * level);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                currentAngle += angleDelta;
                ++startSample;
            }
*/
        }
    }
}
void TuxSynthVoice::setCurrentPlaybackSampleRate (double newRate)
{
    SynthesiserVoice::setCurrentPlaybackSampleRate (newRate);
}
