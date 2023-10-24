#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>

#include "Canvas/Magic/MagicConstants.h"

#include "TuxSynthSound.h"
#include "TuxSynthVoice.h"
#include "OscillatorCoefficients.h"
#include "OscilloscopeData.h"
#include "TuxConstants.h"

#if (MSVC)
#include "ipps.h"
#endif

class PluginProcessor : public juce::AudioProcessor, public juce::AudioProcessorParameter::Listener

{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {};


    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    TuxConstants::TuxInternalParameters& getInternalParameters();

    juce::Image* getCanvas();
    OscilloscopeData& getOsciloscopeData();

private:
    std::vector<float> oscilloscopeSamples;
    OscilloscopeData oscilloscopeData;

    juce::Synthesiser synthesiser;
    const int NUM_SYNTH_VOICES = 16;

    bool wavtablePositionNeedsUpdating;
    void updateWavtablePosition();

    juce::Image canvas;

    TuxConstants::TuxInternalParameters internalParams;
    OscillatorCoefficients oscillatorCoefficients;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
