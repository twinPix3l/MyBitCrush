#include "PluginProcessor.h"

#define NAME_DW "dw"
#define DEFAULT_DW 0.5f

#define NAME_BD "bd"
#define DEFAULT_BD 32

//#define NAME_NS "ns"
//#define DEFAULT_NS 512

#define NAME_RT "rt"
#define DEFAULT_RT 1.0f

using namespace juce;

//==============================================================================
MyBitCrushAudioProcessor::MyBitCrushAudioProcessor()
    : parameters(*this, nullptr, "MyBitCrushParameters", {
        std::make_unique<AudioParameterFloat>(NAME_DW, "Dry/Wet", 0.0f, 1.0f, DEFAULT_DW),
        std::make_unique<AudioParameterInt>(NAME_BD, "Bit Depth", 1, 32, DEFAULT_BD),
        //std::make_unique<AudioParameterInt>(NAME_NS, "N Samples", 1, 512, DEFAULT_NS)
        std::make_unique<AudioParameterFloat>(NAME_RT, "Rate", NormalisableRange<float>(1.0f, 100.0f), DEFAULT_RT)
    })
{
    parameters.addParameterListener(NAME_DW, this);
    parameters.addParameterListener(NAME_BD, this);
    //parameters.addParameterListener(NAME_NS, this);
    parameters.addParameterListener(NAME_RT, this);

}

MyBitCrushAudioProcessor::~MyBitCrushAudioProcessor()
{
}

//==============================================================================
void MyBitCrushAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    drywetter.prepareToPlay(sampleRate, samplesPerBlock);
    quantizer.prepareToPlay(sampleRate, samplesPerBlock);
    sampler.prepareToPlay(sampleRate, samplesPerBlock);
}

void MyBitCrushAudioProcessor::releaseResources()
{
    drywetter.releaseResources();
    quantizer.releaseResources();
    sampler.releaseResources();
}

void MyBitCrushAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    drywetter.setDry(buffer);

    quantizer.processBlock(buffer);

    sampler.processBlock(buffer);

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

    if (paramID == NAME_BD)
        quantizer.setBitDepth(newValue);

    //if (paramID == NAME_NS)
    //    sampler.setNumSamples(newValue);

    if (paramID == NAME_RT)
        sampler.setRate(newValue);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyBitCrushAudioProcessor();
}
