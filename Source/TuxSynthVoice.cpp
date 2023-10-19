//
// Created by arden on 10/16/23.
//

#include "TuxSynthVoice.h"
#include "TuxSynthSound.h"

TuxSynthVoice::TuxSynthVoice()
{

}

bool TuxSynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<TuxSynthSound*> (sound) != nullptr;
}

void TuxSynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    noteOn = true;
    tailOff = 0.0;
    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    oscillator->setFrequency((float)cyclesPerSecond);
    oscillator->setMagnitude(1);
    oscillator->setStartingPhase(0);
    oscillator->reset();
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
            oscillator->processBlock(outputBuffer.getWritePointer(0,startSample), numSamples);

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
    oscillator = std::make_unique<Oscillator>(newRate);
}
