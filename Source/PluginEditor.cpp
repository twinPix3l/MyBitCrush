
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

using namespace juce;

//==============================================================================
MyBitCrushAudioProcessorEditor::MyBitCrushAudioProcessorEditor (MyBitCrushAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), parameters (vts) // inizialiser list
{

  dwSlider.reset (new juce::Slider ("Dry/Wet"));
  addAndMakeVisible (dwSlider.get());
  dwSlider->setValue (0.5);
  dwSlider->setRange (0, 1.0, 0);
  dwSlider->setSliderStyle (juce::Slider::LinearHorizontal);
  dwSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

  dwSlider->setBounds (160, 32, 500, 16);

  bdSlider.reset (new juce::Slider ("BitDepth"));
  addAndMakeVisible (bdSlider.get());
  bdSlider->setValue (32);
  bdSlider->setRange (1, 32, 1);
  bdSlider->setSliderStyle (juce::Slider::LinearHorizontal);
  bdSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

  bdSlider->setBounds (160, 64, 500, 16);

  rtSlider.reset (new juce::Slider ("Rate"));
  addAndMakeVisible (rtSlider.get());
  dwSlider->setValue (0.5);
  rtSlider->setRange (1, 70, 0);
  rtSlider->setSliderStyle (juce::Slider::LinearHorizontal);
  rtSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

  rtSlider->setBounds (160, 96, 500, 16);

  mdButton.reset (new juce::ToggleButton ("Invert"));
  addAndMakeVisible (mdButton.get());

  mdButton->setBounds (160, 128, 72, 24);

  dwAttachment.reset(new SliderAttachment(parameters, NAME_DW, *dwSlider));
  bdAttachment.reset(new SliderAttachment(parameters, NAME_BD, *bdSlider));
  rtAttachment.reset(new SliderAttachment(parameters, NAME_RT, *rtSlider));
  mdAttachment.reset(new ButtonAttachment(parameters, NAME_MD, *mdButton));

  dwLabel.reset (new juce::Label ("Dry/Wet"));
  addAndMakeVisible (dwLabel.get());
  dwLabel->setText("Dry/Wet", juce::dontSendNotification);
  dwLabel->attachToComponent(dwSlider.get(), true);

  bdLabel.reset (new juce::Label ("Bit Depth"));
  addAndMakeVisible (bdLabel.get());
  bdLabel->setText("Bit Depth", juce::dontSendNotification);
  bdLabel->attachToComponent(bdSlider.get(), true);

  rtLabel.reset (new juce::Label ("Rate"));
  addAndMakeVisible (rtLabel.get());
  rtLabel->setText("Rate", juce::dontSendNotification);
  rtLabel->attachToComponent(rtSlider.get(), true);

  setSize (800, 400);

}

MyBitCrushAudioProcessorEditor::~MyBitCrushAudioProcessorEditor()
{
  dwAttachment = nullptr;
  bdAttachment = nullptr;
  rtAttachment = nullptr;
  mdAttachment = nullptr;
  //[/Destructor_pre]

  dwSlider = nullptr;
  bdSlider = nullptr;
  rtSlider = nullptr;
  mdButton = nullptr;

  dwLabel = nullptr;
  bdLabel = nullptr;
  rtLabel = nullptr;

}

//==============================================================================
void MyBitCrushAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black); //fillAll = metodo del graphic context
}

void MyBitCrushAudioProcessorEditor::resized()
{
}
