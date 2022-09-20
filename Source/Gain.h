#pragma once
#include <JuceHeader.h>

#define LEVEL_SMOOTHING_TIME 0.02f

class GainFader
{
public:
  GainFader() {};
  ~GainFader() {};

void prepareToPlay(double sr, int maxNumSamples)
{
  smoothedGain.reset(sr, LEVEL_SMOOTHING_TIME);
}

void processBlock(juce::AudioBuffer<float>& buffer)
{
  //juce::ScopedNoDenormals noDenormals;
    
  auto** channelData = buffer.getArrayOfWritePointers();
  auto numChannels = buffer.getNumChannels();
  auto numSamples = buffer.getNumSamples();
  //auto actualGain = gainParameter.get();
  //auto actualGain = gainParameter;

  //smoothedGain.setTargetValue(actualGain);
  smoothedGain.setTargetValue(gainParameter);
  smoothedGain.applyGain(buffer, numSamples);
}

void setGain(float newValue)
{
  //smoothedGain.setTargetValue(newValue);
  gainParameter = newValue;
}

private:

  //AudioParameterFloat* gainParameter;
  float gainParameter;
  SmoothedValue<float, ValueSmoothingTypes::Linear> smoothedGain; 

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainFader);
};

