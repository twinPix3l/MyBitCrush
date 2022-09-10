
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace juce;

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

class MyBitCrushAudioProcessorEditor : public juce::AudioProcessorEditor/*,
                                        //private Slider::Listener/*,
                                        //private AudioProcessorParameter::Listener*/
{
public:
    MyBitCrushAudioProcessorEditor (MyBitCrushAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~MyBitCrushAudioProcessorEditor() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    MyBitCrushAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& parameters;

    std::unique_ptr<SliderAttachment> dwAttachment;
    std::unique_ptr<SliderAttachment> bdAttachment;
    std::unique_ptr<SliderAttachment> rtAttachment;
    std::unique_ptr<ButtonAttachment> mdAttachment;

    std::unique_ptr<juce::Slider> dwSlider;
    std::unique_ptr<juce::Slider> bdSlider;
    std::unique_ptr<juce::Slider> rtSlider;
    std::unique_ptr<juce::ToggleButton> mdButton;

    std::unique_ptr<juce::Label> dwLabel;
    std::unique_ptr<juce::Label> bdLabel;
    std::unique_ptr<juce::Label> rtLabel;
    std::unique_ptr<juce::Label> mdLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyBitCrushAudioProcessorEditor) //MACRO DI JUCE = "VolumeFaderAudioProcessorEditor" deve essere dichiarata non copyable
                                                                                   //                 e gli viene collegato un memory leak detector
};
