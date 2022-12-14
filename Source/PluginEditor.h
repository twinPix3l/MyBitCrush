
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//#include "BinaryData.h"

using namespace juce;

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

class MyBitCrushAudioProcessorEditor : public juce::AudioProcessorEditor
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
    std::unique_ptr<SliderAttachment> fqAttachment;
    std::unique_ptr<SliderAttachment> amAttachment;
    std::unique_ptr<SliderAttachment> wfAttachment;
    std::unique_ptr<SliderAttachment> gpAttachment;

    std::unique_ptr<juce::Slider> dwSlider;
    std::unique_ptr<juce::Slider> bdSlider;
    std::unique_ptr<juce::Slider> rtSlider;
    std::unique_ptr<juce::ToggleButton> mdButton;
    std::unique_ptr<juce::Slider> fqSlider;
    std::unique_ptr<juce::Slider> amSlider;
    std::unique_ptr<juce::Slider> wfSlider;
    std::unique_ptr<juce::Slider> gpSlider;

    std::unique_ptr<juce::Label> dwLabel;
    std::unique_ptr<juce::Label> bdLabel;
    std::unique_ptr<juce::Label> rtLabel;
    std::unique_ptr<juce::Label> mdLabel;
    std::unique_ptr<juce::Label> fqLabel;
    std::unique_ptr<juce::Label> amLabel;
    std::unique_ptr<juce::Label> wfLabel;
    std::unique_ptr<juce::Label> gpLabel;

    //juce::Image btj = ImageFileFormat::loadFrom (File("/home/yost/Documents/juce_projects/MyBitCrush/beetlejuice1.jpeg"));
    juce::Image btj = ImageFileFormat::loadFrom (BinaryData::beetlejuice1_jpeg, BinaryData::beetlejuice1_jpegSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyBitCrushAudioProcessorEditor)
};
