#pragma once
#include <JuceHeader.h>

#define NAME_DW "dw"
#define DEFAULT_DW 0.5f

#define NAME_BD "bd"
#define DEFAULT_BD 32

#define NAME_RT "rt"
#define DEFAULT_RT 1
#define MAX_RT 70

#define NAME_MD "md"
#define DEFAULT_MD false

#define NAME_FQ "fq"
#define DEFAULT_FQ 0.1f

#define NAME_AM "am"
#define DEFAULT_AM 0

#define NAME_WF "waveform"
#define DEFAULT_WF 0

#define NAME_GP "Gain"
#define DEFAULT_GP 1.0f

using namespace juce;

namespace Parameters
{
  static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
  {
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>(NAME_DW, "Dry/Wet", 0.0f, 1.0f, DEFAULT_DW));
    params.push_back(std::make_unique<AudioParameterInt>(NAME_BD, "BitDepth", 1, 32, DEFAULT_BD));
    params.push_back(std::make_unique<AudioParameterInt>(NAME_RT, "Rate", 1, MAX_RT, DEFAULT_RT));
    params.push_back(std::make_unique<AudioParameterBool>(NAME_MD, "Invert", DEFAULT_MD));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_FQ, "LFO freq (Hz)", NormalisableRange<float>(0.1f, 20.0f, 0.01f, 0.5f), DEFAULT_FQ));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_AM, "Mod amount", 0.0f, MAX_RT / 2.0f, DEFAULT_AM));
    params.push_back(std::make_unique<AudioParameterChoice>(NAME_WF, "LFO shape", StringArray{"Sine", "Triangle", "Saw Up", "Saw Down", "Square"}, DEFAULT_WF));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_GP, "Volume", 0.0f, 1.0f, DEFAULT_GP));
    
    return {params.begin(), params.end()};
  }
}