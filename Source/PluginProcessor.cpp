#include "PluginProcessor.h"
#include "Parameters.h"

#define NAME_DW "dw"
#define DEFAULT_DW 0.5f

#define NAME_BD "bd"
#define DEFAULT_BD 32

//#define NAME_NS "ns"
//#define DEFAULT_NS 512

#define NAME_RT "rt"
#define DEFAULT_RT 1.0f

#define NAME_MD "md"
#define DEFAULT_MD 0

//using namespace juce;

//==============================================================================
MyBitCrushAudioProcessor::MyBitCrushAudioProcessor()
    : parameters(*this, nullptr, "MyBitCrushParameters", Parameters::createParameterLayout())
{
    parameters.addParameterListener(NAME_DW, this);
    parameters.addParameterListener(NAME_BD, this);
    //parameters.addParameterListener(NAME_NS, this);
    parameters.addParameterListener(NAME_RT, this);
    parameters.addParameterListener(NAME_MD, this);

    drywetter.setDryWetRatio(DEFAULT_DW);
    quantizer.setBitDepth(DEFAULT_BD);
    sampler.setRate(DEFAULT_RT);
    modder.setMode(DEFAULT_MD);
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
    
    switch (modder.getMode()) {

        case 0:
            quantizer.processBlock(buffer);
            sampler.processBlock(buffer);
        
        case 1:
            sampler.processBlock(buffer);
            quantizer.processBlock(buffer);
    }

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
    
    if (paramID == NAME_MD)
        modder.setMode(newValue);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyBitCrushAudioProcessor();
}
