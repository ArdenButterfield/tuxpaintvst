#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "TuxConstants.h"

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), tuxPaint(p.getInternalParameters(), p.getCanvas(),p.getOsciloscopeData())
{
    juce::ignoreUnused (processorRef);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (640, 500);
    addAndMakeVisible(tuxPaint);
}

PluginEditor::~PluginEditor()
{

}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PluginEditor::resized()
{
    // lay out the positions of your components
    tuxPaint.setBounds(getLocalBounds());
}
