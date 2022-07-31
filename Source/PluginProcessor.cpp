#include "PluginProcessor.h"

#define NAME_DW "dw"
#define DEFAULT_DW 0.5f

using namespace juce;

//==============================================================================
MyBitCrushAudioProcessor::MyBitCrushAudioProcessor()
    : parameters(*this, nullptr, "MyBitCrushParameters", {
        std::make_unique<AudioParameterFloat>(NAME_DW, "Dry/Wet", 0.0f, 1.0f, DEFAULT_DW)
    })
{
    parameters.addParameterListener(NAME_DW, this);
}

MyBitCrushAudioProcessor::~MyBitCrushAudioProcessor()
{
}

//==============================================================================
void MyBitCrushAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    drywetter.prepareToPlay(sampleRate, samplesPerBlock);
}

void MyBitCrushAudioProcessor::releaseResources()
{
    drywetter.releaseResources();
}

void MyBitCrushAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    drywetter.setDry(buffer);

    // bitcrush.processblock(buffer);

    drywetter.merge(buffer);
}

//==============================================================================
juce::AudioProcessorEditor* MyBitCrushAudioProcessor::createEditor()
{
    return nullptr;
}

//==============================================================================
void MyBitCrushAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MyBitCrushAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void MyBitCrushAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == NAME_DW)
        drywetter.setDryWetRatio(newValue);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyBitCrushAudioProcessor();
}
