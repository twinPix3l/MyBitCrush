#pragma once
#include <JuceHeader.h>

#define NAME_DW "dw"
#define DEFAULT_DW 0.5f

#define NAME_BD "bd"
#define DEFAULT_BD 32

//#define NAME_NS "ns"
//#define DEFAULT_NS 512

#define NAME_RT "rt"
#define DEFAULT_RT 1.0f
#define MAX_RT 70.0f

#define NAME_MD "md"
#define DEFAULT_MD 0

#define NAME_FQ "fq"
#define DEFAULT_FQ 1

#define NAME_AM "am"
#define DEFAULT_AM 0

using namespace juce;

namespace Parameters
{
  static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
  {
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>(NAME_DW, "Dry/Wet", 0.0f, 1.0f, DEFAULT_DW));
    params.push_back(std::make_unique<AudioParameterInt>(NAME_BD, "BitDepth", 1, 32, DEFAULT_BD));
    //std::make_unique<AudioParameterInt>(NAME_NS, "N Samples", 1, 512, DEFAULT_NS)
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_RT, "Rate", NormalisableRange<float>(1.0f, MAX_RT), DEFAULT_RT));
    params.push_back(std::make_unique<AudioParameterBool>(NAME_MD, "Invert", DEFAULT_MD));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_FQ, "LFO freq (Hz)", NormalisableRange<float>(0.1f, 20.0f, 0.01f, 0.3f), DEFAULT_FQ));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_AM, "Mod amount", NormalisableRange<float>(0.0f, MAX_RT / 2.0f, 0.001f), DEFAULT_AM));
    
    return {params.begin(), params.end()};
  }
}