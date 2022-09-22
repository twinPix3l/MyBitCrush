#pragma once
#include "math.h"

#include <JuceHeader.h>
#include "Parameters.h"

#define GLIDE_TIME 0.01f
#define SMOOTHING_TIME 0.02f

using namespace juce;

class NaiveOscillator
{
public:
	NaiveOscillator() {};
	~NaiveOscillator() {};

	void prepareToPlay(double sr)
	{
		samplePeriod = 1 / sr;
		frequency.reset(sr, GLIDE_TIME);
	}

	void setFrequency(float newValue)
	{
		frequency.setTargetValue(newValue);
	}

	void setWaveform(int newValue)
	{
		waveform = newValue;
	}

	void getNextAudioBlock(AudioBuffer<float>& buffer, const int numSamples)
	{
		const int numCh = buffer.getNumChannels();
		auto bufferData = buffer.getArrayOfWritePointers();

		for (int smp = 0; smp < numSamples; smp++)
		{
			const auto sampleValue = getNextAudioSample();

			for (int ch = 0; ch < numCh; ch++)
				bufferData[ch][smp] = sampleValue;
		}
	}

	float getNextAudioSample()
	{
		auto sampleValue = 0.0f;

		switch (waveform)
		{
			// Sine wave
			case 0: 
				sampleValue = sin(MathConstants<float>::twoPi * currentPhase);
				break;

			// Triangle wave
			case 1: 
				sampleValue = 4.0f * (std::fabs(currentPhase - 0.5f)) - 1.0f;
				break;

			// Saw Up wave
			case 2: 
				sampleValue = 2.0f * currentPhase - 1.0f;
				break;

			// Saw Down wave
			case 3:
				sampleValue = -2.0f * currentPhase - 1.0f;
				break;

			// Square wave
			case 4:
				sampleValue = (currentPhase > 0.5f) - (currentPhase < 0.5f);
				break;
		}

		//phaseIncrement = frequency.isSmoothing() ? frequency.getNextValue() * samplePeriod : phaseIncrement;
		phaseIncrement = frequency.getNextValue() * samplePeriod;
		currentPhase += phaseIncrement;
		currentPhase -= static_cast<int>(currentPhase);

		return sampleValue;
	}

private:

	double samplePeriod = 1.0f;
	float currentPhase = 0.0f;
	float phaseIncrement = 0.0f;
	SmoothedValue<float, ValueSmoothingTypes::Multiplicative> frequency;
	
	int waveform = 0;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NaiveOscillator)
};

class RateModulation
{
public:
	RateModulation() {};
	~RateModulation() {};

	void prepareToPlay(double sr)
	{
		parameter.reset(sr, SMOOTHING_TIME);
		modAmount.reset(sr, SMOOTHING_TIME);
	}

	void setParameter(int newValue)
	{
		parameter.setTargetValue(newValue);
	}

	void setModAmount(float newValue)
	{
		modAmount.setTargetValue(newValue);
	}

	void processBlock(AudioBuffer<float>& buffer, const int numSamples)
	{
		auto bufferData = buffer.getArrayOfWritePointers();

		auto numCh = buffer.getNumChannels();

		// Scalo la modulante tra 0 e 1
		for (int ch = 0; ch < numCh; ch++)
		{
			FloatVectorOperations::add(bufferData[ch], 1.0f, numSamples);
			FloatVectorOperations::multiply(bufferData[ch], 0.5f, numSamples);
			//std::cout << bufferData[ch];
		}
	

		// Scalo la modulante tra 0 e la modulazione massima desiderata
		modAmount.applyGain(buffer, numSamples);

		// Sommo alla modulante il rate proveniente dal parametro
		if (parameter.isSmoothing())
			for (int smp = 0; smp < numSamples; smp++)
			{
				const auto param = parameter.getNextValue();

				for (int ch = 0; ch < numCh; ch++)
				{  
					bufferData[ch][smp] += param;
				}
			}
		else
			for (int ch = 0; ch < numCh; ch++)
			{  
				FloatVectorOperations::add(bufferData[ch], parameter.getCurrentValue(), numSamples);
			}
			// Controllo di esssere dentro al rate massimo  
			for (int ch = 0; ch < numCh; ch++)
				FloatVectorOperations::min(bufferData[ch], bufferData[ch], MAX_RT, numSamples);
	}

private:

	SmoothedValue<int, ValueSmoothingTypes::Linear> parameter;
	SmoothedValue<float, ValueSmoothingTypes::Linear> modAmount;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RateModulation)
};