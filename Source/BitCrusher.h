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

    int qLevels = powf(2, bitDepth - 1);
    
    for (int smp = 0; smp <= buffer.getNumSamples(); smp++ )
    {
      
      for (int ch = buffer.getNumChannels(); --ch >= 0; )
      {
        
        float *val = buffer.getWritePointer(ch);
        
        if (val[smp] >= 0)
          val[smp] = ceil(val[smp] * qLevels) / qLevels;
        else
          val[smp] = floor(val[smp] * qLevels) / qLevels;
      }
    }
  };

  void setBitDepth(int newValue)
  {
    bitDepth = newValue;
  }

private:

  int bitDepth;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Quantizer);
};

class Sampler
{
public:
  Sampler() {}
  ~Sampler() {}

  void prepareToPlay(double sampleRate, int maxNumSamples)
  {
    setNumSamples(numSamples);
  }

  void releaseResources()
  {

  }

  void processBlock(AudioBuffer<float>& buffer)
  {
    unsigned int t;

    for (int smp = 0; smp <= buffer.getNumSamples(); smp++ )
    {
      for (int ch = buffer.getNumChannels(); --ch >= 0; )
      {
        float *val = buffer.getWritePointer(ch);
        
        if ( ++t%numSamples != 0 || numSamples == 1)
          val[smp] = val[smp - 1];
      }
    }
  }

  void setNumSamples(float newValue)
  {
    numSamples = newValue;
  }

private:

  int numSamples;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Sampler);
};