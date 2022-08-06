#pragma once

#include <JuceHeader.h>

#define LEVEL_SMOOTHING_TIME 0.02f

class DryWet
{
public:
  DryWet() {}
  ~DryWet() {}

  void prepareToPlay(double sr, int maxNumSamples)
  {
    drySignal.setSize(2, maxNumSamples);
    dryLevel.reset(sr, LEVEL_SMOOTHING_TIME);
    wetLevel.reset(sr, LEVEL_SMOOTHING_TIME);
    setDryWetRatio(dryWetRatio);
  }

  void releaseResources()
  {
    drySignal.setSize(0, 0);
  }

  void setDry(const AudioBuffer<float>& buffer)
  {
    for (int ch = buffer.getNumChannels(); --ch >= 0; ) {
      drySignal.copyFrom(ch, 0, buffer, ch, 0, buffer.getNumSamples()); 
    }
  }

  void merge(AudioBuffer<float>& buffer)
  {
    //buffer.applyGain(wetLevel);
    //drySignal.applyGain(dryLevel); // sostituito dall'ultimo input del metodo addFrom
    auto numSamples = buffer.getNumSamples();
    dryLevel.applyGain(drySignal, numSamples);
    wetLevel.applyGain(buffer, numSamples);
    
    for (int ch = buffer.getNumChannels(); --ch >= 0; ) 
    {
      //buffer.addFrom(ch, 0, drySignal, ch, 0, buffer.getNumSamples(), dryLevel);
      buffer.addFrom(ch, 0, drySignal, ch, 0, numSamples); 
    }
  }

  void setDryWetRatio(const float newValue)
  {
    dryWetRatio = newValue;
    //dryLevel = sqrt(1 - dryWetRatio);
    dryLevel.setTargetValue(sqrt(1 - dryWetRatio));
    //wetLevel = sqrt(dryWetRatio);
    wetLevel.setTargetValue(sqrt(dryWetRatio));
  }

private:
  
  float dryWetRatio = 0.5;
  //float dryLevel;
  //float wetLevel;
  SmoothedValue<float, ValueSmoothingTypes::Linear> dryLevel;
  SmoothedValue<float, ValueSmoothingTypes::Linear> wetLevel;

  AudioBuffer<float> drySignal;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};
