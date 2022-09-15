#include "PluginProcessor.h"
#include "Parameters.h"
#include "PluginEditor.h"

// using namespace juce;

//==============================================================================
MyBitCrushAudioProcessor::MyBitCrushAudioProcessor()
    : parameters(*this, nullptr, "MyBitCrushParameters", Parameters::createParameterLayout())
{
    parameters.addParameterListener(NAME_DW, this);
    parameters.addParameterListener(NAME_BD, this);
    // parameters.addParameterListener(NAME_NS, this);
    parameters.addParameterListener(NAME_RT, this);
    parameters.addParameterListener(NAME_MD, this);
    parameters.addParameterListener(NAME_FQ, this);
    parameters.addParameterListener(NAME_AM, this);
    parameters.addParameterListener(NAME_WF, this);

    drywetter.setDryWetRatio(DEFAULT_DW);
    quantizer.setBitDepth(DEFAULT_BD);
    //sampler.setRate(DEFAULT_RT);
    modder.setMode(DEFAULT_MD);
    LFO.setFrequency(DEFAULT_FQ);
    LFO.setWaveform(DEFAULT_WF);
    rateAdapter.setModAmount(DEFAULT_AM);
    rateAdapter.setParameter(DEFAULT_RT);
}

MyBitCrushAudioProcessor::~MyBitCrushAudioProcessor()
{
}

//==============================================================================
void MyBitCrushAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    drywetter.prepareToPlay(sampleRate, samplesPerBlock);
    quantizer.prepareToPlay(sampleRate, samplesPerBlock);
    //sampler.prepareToPlay(sampleRate, samplesPerBlock);
    modSampler.prepareToPlay(sampleRate, samplesPerBlock);
    LFO.prepareToPlay(sampleRate);
    modulationSignal.setSize(2, samplesPerBlock);
    rateAdapter.prepareToPlay(sampleRate);
}

void MyBitCrushAudioProcessor::releaseResources()
{
    drywetter.releaseResources();
    quantizer.releaseResources();
    //sampler.releaseResources();
    modSampler.releaseResources();
    modulationSignal.setSize(0, 0);
}

void MyBitCrushAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    const auto numSamples = buffer.getNumSamples();

    // Genero una modulante
    LFO.getNextAudioBlock(modulationSignal, numSamples);

    // Scalare la modulante
    rateAdapter.processBlock(modulationSignal, numSamples);

    drywetter.setDry(buffer);

    switch (modder.getMode())
    {
    case 0:
        quantizer.processBlock(buffer);
        modSampler.processBlock(buffer, modulationSignal);
        break;

    case 1:
        modSampler.processBlock(buffer, modulationSignal);
        quantizer.processBlock(buffer);
        break;
    }

    drywetter.merge(buffer);

    // Listen to the waves
    //LFO.getNextAudioBlock(buffer, buffer.getNumSamples());
}

//==============================================================================
juce::AudioProcessorEditor *MyBitCrushAudioProcessor::createEditor()
{
    return new MyBitCrushAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void MyBitCrushAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MyBitCrushAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void MyBitCrushAudioProcessor::parameterChanged(const String &paramID, float newValue)
{
    if (paramID == NAME_DW)
        drywetter.setDryWetRatio(newValue);

    if (paramID == NAME_BD)
        quantizer.setBitDepth(newValue);

    if (paramID == NAME_RT)
        //sampler.setRate(newValue);
        rateAdapter.setParameter(newValue);

    if (paramID == NAME_MD)
        modder.setMode(newValue);

    if (paramID == NAME_FQ)
        LFO.setFrequency(newValue);

    if (paramID == NAME_AM)
        rateAdapter.setModAmount(newValue);
    
    if (paramID == NAME_WF)
        LFO.setWaveform(newValue);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new MyBitCrushAudioProcessor();
}
