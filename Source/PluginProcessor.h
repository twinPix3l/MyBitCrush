#pragma once

#include <JuceHeader.h>
#include "DryWet.h"
#include "BitCrusher.h"
#include "LFO.h"
#include "Gain.h"

class MyBitCrushAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
	//==============================================================================
	MyBitCrushAudioProcessor();
	~MyBitCrushAudioProcessor() override;

	//==============================================================================
	void prepareToPlay (double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

	void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	//==============================================================================
	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override               {return true; }

	//==============================================================================
	const juce::String getName() const override   {return "BitleJuce"; }

	bool acceptsMidi() const override             {return false; }
	bool producesMidi() const override            {return false; }
	bool isMidiEffect() const override            {return false; }
	double getTailLengthSeconds() const override  {return 0.0; }

	//==============================================================================
	int getNumPrograms() override                {return 1; }
	int getCurrentProgram() override             {return 0; }
	void setCurrentProgram (int index) override  {}
	const juce::String getProgramName (int index) override  {return {}; }
	void changeProgramName (int index, const juce::String& newName) override {}

	//==============================================================================
	void getStateInformation (juce::MemoryBlock& destData) override;
	void setStateInformation (const void* data, int sizeInBytes) override;

private:

	void parameterChanged(const String& paramID, float newValue) override;
	
	AudioProcessorValueTreeState parameters;

	DryWet drywetter;

	Quantizer quantizer;

	//Sampler sampler;
	ModSampler modSampler;

	//Modder modder;
	bool invert;

	NaiveOscillator LFO;

	RateModulation rateAdapter;

	AudioBuffer<float> modulationSignal;

	GainFader gainFader;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyBitCrushAudioProcessor)
};
