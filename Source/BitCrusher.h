#pragma once
#include <JuceHeader.h>

class Quantizer
{
public:
	Quantizer() {}
	~Quantizer() {}

	void prepareToPlay(double sampleRate, int maxNumSamples)
	{
		setBitDepth(bitDepth);
	}

	void releaseResources()
	{
	}

	void processBlock(AudioBuffer<float>& buffer)
  	{
		for (int ch = buffer.getNumChannels(); --ch >= 0; )
		{
	  		float *val = buffer.getWritePointer(ch);
	  
	  		for (int smp = 0; smp < buffer.getNumSamples(); smp++ )
	  		{
				if (bitDepth > 1)
				{          
					qLevels = powf(2, bitDepth - 1) / 2;
		
		  			val[smp] = (val[smp] >= 0) ? ceil(val[smp] * qLevels) / qLevels
								   : floor(val[smp] * qLevels) / qLevels;
		  			//val[smp] = ( floor(val[smp] * qLevels ) ) / qLevels;

		  			if (val[smp] > 1) val[smp] = 1;
		  			if (val[smp] < -1) val[smp] = -1;

					hold[ch] = val[smp];
				}
				else
				{
					val[smp] = hold[ch];
				}
	  		}
		}
  	}

  	void setBitDepth(int newValue)
  	{
		bitDepth = newValue;
  	}

private:

  	int bitDepth = 0;
  	int qLevels = 1;
	float hold[2] = {0.0f, 0.0f};

  	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Quantizer);
};

class Sampler
{
public:
  	Sampler() {}
  	~Sampler() {}

  	void prepareToPlay(double sampleRate, int maxNumSamples)
  	{
		rate.reset(sampleRate, LEVEL_SMOOTHING_TIME);
  	}

  	void releaseResources()
  	{
  	}

  	void processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& rateBuffer)
  	{
		for (int ch = buffer.getNumChannels(); --ch >= 0; ) 
		{
	  		for (unsigned int smp = 0; smp < buffer.getNumSamples(); smp++ )
	  		{
				float *val = buffer.getWritePointer(ch);

				if (rate.getCurrentValue() > 1)
				{
		  			//if ( smp%(buffer.getNumSamples() - numSamples) != 0 ) 
		  			if ( smp%(rate.getCurrentValue()) != 0 )
						val[smp] = val[smp - 1];
				}
	  		}
		}
  	}

  	void setRate(int newValue)
  	{
		rate.setTargetValue(newValue);
  	}

private:
  
	SmoothedValue<int, ValueSmoothingTypes::Linear> rate;

  	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Sampler);
};

class ModSampler
{
public:
  	ModSampler() {}
  	~ModSampler() {}

  	void prepareToPlay(double sampleRate, int maxNumSamples)
  	{
  	}

  	void releaseResources()
  	{
 	}

  	void processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& rateBuffer)
  	{
		const auto numChannels = buffer.getNumChannels();
		const auto numSamples = buffer.getNumSamples();
		const float *rateVal = rateBuffer.getReadPointer(0);

		for (int ch = 0; ch < numChannels; ch++ )
		{
	  		for (unsigned int smp = 0; smp < numSamples; smp++ )
	  		{
				float *val = buffer.getWritePointer(ch);
				if (rateVal[0] > 1)
				{
		  			// Tentativo 1 di gestione dei casi limite
		  			//if ( ( ( smp % static_cast<int>(rateVal[0]) ) - offset ) != 0)
		  			//  val[smp] = ((smp - offset) < 0) ? oldSample[ch] : val[smp - 1];
		  
		  			// Tentativo 2 di gestione dei casi limite (le espressioni sono equivalenti)
		  			//val[smp] = ( smp + offset ) % static_cast<int>(rateVal[ch]) == 0 ? val[smp] : oldSample[ch];
		  			if ( ! ( ( smp + offset ) % static_cast<int>(rateVal[0]) ) ) val[smp] = oldSample[ch];
				}
				// Aggiorno oldSample  
				oldSample[ch] = buffer.getSample(ch, numSamples - 1);    
	  		}
			
		}
		// Aggiorno l'offset
		if (rateVal[0] > 1)
		{
	  		//offset += ( (static_cast<int>(rateVal[ch]) - 1 ) ) -
			//          ( (numSamples - 1 ) % static_cast<int>(rateVal[ch]) );
  			//offset = offset % static_cast<int>(rateVal[ch]);
  			offset = ( numSamples + offset ) % static_cast<int>(rateVal[0]);
		}		
  	}

private:

  	int offset = 0;
  	float oldSample[2] = {0.0f, 0.0f};

  	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModSampler);
};
