//
// Created by arden on 10/16/23.
//

#include "TuxSynthVoice.h"
#include "TuxSynthSound.h"

TuxSynthVoice::TuxSynthVoice(OscillatorCoefficients* c) : coefficients(c)
{

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
    oscillators.resize(coefficients->getNumCoefficients());
    noteOn = true;
    tailOff = 0.0;
    auto cyclesPerSecond = (float)juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    maxHarmonic = coefficients->getMaxHarmonic(cyclesPerSecond);
    for (int i = 0; i < maxHarmonic; ++i) {
        oscillators[i].setSamplerate((float)getSampleRate());
        oscillators[i].setFrequency(cyclesPerSecond * (float)i);
        oscillators[i].setMagnitude(coefficients->getMagnitude(cyclesPerSecond, i));
        oscillators[i].setStartingPhase(coefficients->getPhase(cyclesPerSecond, i));
        oscillators[i].reset();
    }
}

void TuxSynthVoice::stopNote (float, bool allowTailOff)
{
    noteOn = false;
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
            for (int i = 0; i < maxHarmonic; ++i) {

                oscillators[i].processBlock(outputBuffer.getWritePointer(0,startSample), numSamples);
            }

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
