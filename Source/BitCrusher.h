#pragma once
#include <JuceHeader.h>

class DeQuantizer
{
public:
  DeQuantizer() {}
  ~DeQuantizer() {}

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
    int smp;

    for (int smp = 0; smp <= buffer.getNumSamples(); smp++ )
    {
      for (int ch = buffer.getNumChannels(); --ch >= 0; )
        {
          float *val = buffer.getWritePointer(ch);
          val[smp] = round(val[smp] * qLevels) / qLevels;
        } 
    }
      

  }

  void setBitDepth(int newValue)
  {
    bitDepth = newValue;
  }

private:

  int bitDepth;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeQuantizer);
};

class DownSampler
{
public:
  DownSampler() {}
  ~DownSampler() {}

  void prepareToPlay(double sampleRate, int maxNumSamples)
  {
    setNumSamples(numSamples);
  }

  void releaseResources()
  {

  }

  void processBlock(AudioBuffer<float>& buffer)
  {

  }

  void setNumSamples(float newValue)
  {
    numSamples = newValue;
  }

private:

  int numSamples;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DownSampler);
};