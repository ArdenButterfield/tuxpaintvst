#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

juce::AudioProcessorValueTreeState::ParameterLayout makeParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID {"tool", 1},
        "Tool",
        juce::StringArray {
            // Freehand painting tool
            "Paint",

            // Stamp tool (aka Rubber Stamps
            "Stamp",

            // Line drawing tool
            "Lines",

            // Shape creation tool (square, circle, etc.
            "Shapes",

            // Text tool
            "Text",

            // Label tool
            "Label",

            // Fill tool
            "Fill",

            // "Magic" effects tools (blur, flip image, etc.
            "Magic",

            // Undo last action
            "Undo",

            // Redo undone action
            "Redo",

            // Eraser tool
            "Eraser",

            // Start a new picture
            "New",

            // Open a saved picture
            "Open",

            // Save the current picture
            "Save"
        },
        0));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"shapes", 1},
        "Shapes",
        juce::StringArray {
            // Square shape tool (4 equally-lengthed sides at right angles)
            "Square",
            "Square",

            // Rectangle shape tool (4 sides at right angles)
            "Rectangle",
            "Rectangle",

            // Circle shape tool (X radius and Y radius are the same)
            "Circle",
            "Circle",

            // Ellipse shape tool (X radius and Y radius may differ)
            "Ellipse",
            "Ellipse",

            // Triangle shape tool (3 sides)
            "Triangle",
            "Triangle",

            // Pentagon shape tool (5 sides)
            "Pentagon",
            "Pentagon",

            // Hexagon shape tool (6 sides)
            "Hexagon",
            "Hexagon",

            // Heptagon (aka septagon) shape tool (7 sides)
            "Heptagon",
            "Heptagon",

            // Octagon shape tool (8 sides)
            "Octagon",
            "Octagon",

            // Rhombus shape tool (4 sides, not at right angles)
            "Rhombus",
            "Rhombus",

            // Triangle star (3 points star)
            "Star",
            "Star",

            // Rhombus star (4 points star)
            "Star",
            "Star",

            // Pentagon star (5 points star)
            "Star",
            "Star"
        },
        0
        ));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"shapeOrigin", 1},
        "Shape Origin",
        juce::StringArray {
            "center",
            "corner"
        },
        0
        ));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"fills", 1},
        "Fills",
        juce::StringArray {
            "Solid",
            "Brush",
            "Linear",
            "Radial",
            "Shaped"
        },
        0
        ));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"erasers", 1},
        "Erasers",
        juce::StringArray {
            "Square 0",
            "Square 1",
            "Square 2",
            "Square 3",
            "Square 4",
            "Square 5",
            "Square 6",
            "Square 7",
            "Circle 0",
            "Circle 1",
            "Circle 2",
            "Circle 3",
            "Circle 4",
            "Circle 5",
            "Circle 6",
            "Circle 7"
        },
        0
        ));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"colors", 1},
        "Colors",
        juce::StringArray { &TuxConstants::default_color_names[0], TuxConstants::NUM_DEFAULT_COLORS},
        0
        ));
    return {parameters.begin(), parameters.end()};
}

PluginProcessor::PluginProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
      parameters(*this, nullptr, juce::Identifier("TuxPaintVST"), makeParameters())

{
}

PluginProcessor::~PluginProcessor()
{
}

//==============================================================================
const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String PluginProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need.
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        juce::ignoreUnused (channelData);
        // ..do something to the data...
    }
}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

juce::AudioProcessorValueTreeState& PluginProcessor::getValueTreeState()
{
    return parameters;
}
void PluginProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
