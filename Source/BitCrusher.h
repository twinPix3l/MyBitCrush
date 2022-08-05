#pragma once
#include <JuceHeader.h>

class DeQuantizer
{
public:
  DeQuantizer() {}
  ~DeQuantizer() {}

  void prepareToPlay(double sampleRate, int maxNumSamples)
  {
    setNumBits(numBits);
  }

  void releaseResources()
  {

  }

  void processBlock(AudioBuffer<float>& buffer)
  {

  }

  void setNumBits(int newValue)
  {
    numBits = newValue;
  }

private:

  int numBits;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeQuantizer);
};

class DownSampler
{
public:
  DownSampler() {}
  ~DownSampler() {}

  void prepareToPlay(double sampleRate, int maxNumSamples)
  {

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

  float numSamples;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DownSampler);
};