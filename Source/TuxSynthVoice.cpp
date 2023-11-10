//
// Created by arden on 10/16/23.
//

#include "TuxSynthVoice.h"
#include "TuxSynthSound.h"

TuxSynthVoice::TuxSynthVoice(OscillatorCoefficients* c) : coefficients(c), filterBaseHarmonic(2), filterEnvelopeStrength(10)
{
    maxHarmonic = 0;
    noteOn = false;
    envelope.setSampleRate(getSampleRate());
    filterEnvelope.setSampleRate(getSampleRate());
    envelope.setParameters({0.0,1.0,0.8,1.0});
    filterEnvelope.setParameters({0.0,1.0,0.8,1.0});
    filter.setCoefficients(juce::IIRCoefficients::makeLowPass(getSampleRate(), getSampleRate() / 2));
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
    envelope.reset();
    filterEnvelope.reset();
    envelope.noteOn();
    filterEnvelope.noteOn();

    filter.reset();

    oscillators.resize(coefficients->getNumCoefficients());
    noteOn = true;
    tailOff = 0.0;
    currentNoteFrequency = (float)juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    maxHarmonic = coefficients->getMaxHarmonic(currentNoteFrequency);
    for (int i = 0; i < maxHarmonic; ++i) {
        oscillators[i].setSamplerate((float)getSampleRate());
        oscillators[i].setFrequency(currentNoteFrequency * (float)i);
        oscillators[i].setMagnitude(coefficients->getMagnitude(currentNoteFrequency, i) * velocity);
        oscillators[i].setStartingPhase(coefficients->getPhase(currentNoteFrequency, i));
        oscillators[i].reset();
    }
}

void TuxSynthVoice::stopNote (float, bool allowTailOff)
{
    envelope.noteOff();
    filterEnvelope.noteOff();
    if (!allowTailOff) {
        clearCurrentNote();
        noteOn = false;
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
    if (noteOn) {
        float filterEnvPosition;
        for (int i = 0; i < numSamples; ++i) {
            filterEnvPosition = filterEnvelope.getNextSample();
        }

        auto filterFreq = (filterEnvPosition * filterEnvelopeStrength * filterBaseHarmonic * currentNoteFrequency) + currentNoteFrequency;
        filterFreq = juce::jmin(filterFreq, (float)getSampleRate() * 0.5f);
        filterFreq = juce::jmax(filterFreq, 10.f);
        filter.setCoefficients(juce::IIRCoefficients::makeLowPass(getSampleRate(), filterFreq));


        auto samples = juce::AudioSampleBuffer(1, numSamples);
        samples.clear();
        for (int i = 0; i < maxHarmonic; ++i) {
            oscillators[i].processBlock(samples.getWritePointer(0,0), numSamples);
        }
        envelope.applyEnvelopeToBuffer(samples,0,numSamples);
        filter.processSamples(samples.getWritePointer(0,0), numSamples);
        outputBuffer.addFrom(0,startSample,samples,0,0,numSamples,1);
        if (!envelope.isActive()) {
            noteOn = false;
            clearCurrentNote();
        }
    }
}
void TuxSynthVoice::setCurrentPlaybackSampleRate (double newRate)
{
    SynthesiserVoice::setCurrentPlaybackSampleRate (newRate);
}
