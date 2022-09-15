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
      
      for (int smp = 0; smp <= buffer.getNumSamples(); smp++ )
      {
        int qLevels = powf(2, bitDepth - 1);

        if ( val[smp] >= 0)
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
    //setRate(rate);
    rate.reset(sampleRate, LEVEL_SMOOTHING_TIME);
  }

  void releaseResources()
  {

  }

  void processBlock(AudioBuffer<float>& buffer)
  {
    for (int ch = buffer.getNumChannels(); --ch >= 0; ) 
    {
      for (unsigned int smp = 0; smp <= buffer.getNumSamples(); smp++ )
      {
        float *val = buffer.getWritePointer(ch);
        //ratio = static_cast<int> (rate);
        std::cout << rate.getCurrentValue();

        //if (numSamples != buffer.getNumSamples())
        if (rate.getCurrentValue() > 1)
        {
          //if ( smp%(buffer.getNumSamples() - numSamples) != 0 ) 
          if ( smp%static_cast<int>(rate.getCurrentValue()) != 0 )
            val[smp] = val[smp - 1];
        }
      }
    }
  }

  void setRate (float newValue)
  {
    rate.setTargetValue(newValue);
  }

private:
  
  SmoothedValue<float, ValueSmoothingTypes::Linear> rate;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Sampler);
};

class Modder
{
public:
  Modder() {}
  ~Modder() {}

  void setMode (bool newValue)
  {
    mode = newValue;
  }

  bool getMode()
  {
    return mode;
  }

private:

  bool mode;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Modder);
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
    const auto numModChannels = rateBuffer.getNumChannels();
    auto rateArray = rateBuffer.getArrayOfReadPointers();

    for (int ch = 0; ch < numChannels; ch++ )
    {
      for (unsigned int smp = 0; smp <= buffer.getNumSamples(); smp++ )
      {
        float *val = buffer.getWritePointer(ch);

        if (rateArray[jmin(ch, numModChannels - 1)][smp] > 1)
        { 
          if ( smp%static_cast<int>(rateArray[jmin(ch, numModChannels - 1)][smp]) != 0 )
            val[smp] = val[smp - 1];
        }
        //std::cout << rateArray[jmin(ch, numModChannels - 1)][smp];
        //std::cout << "                 ";
      } 
    }
  }

private:

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModSampler);
};
