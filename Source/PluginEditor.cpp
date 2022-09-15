
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
  dwSlider->setRange (0, 0.5, 0);
  dwSlider->setValue(DEFAULT_DW);
  dwSlider->Slider::setColour(Slider::trackColourId, Colours::darkseagreen);
  dwSlider->Slider::setColour(Slider::backgroundColourId, Colours::darkred);
  
  dwSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

  dwSlider->setBounds (160, 32, 500, 16);

  bdSlider.reset (new juce::Slider ("BitDepth"));
  addAndMakeVisible (bdSlider.get());
  bdSlider->setRange (1, 32, 1);
  bdSlider->setValue(DEFAULT_BD);
  bdSlider->setSliderStyle (Slider::LinearHorizontal);
  bdSlider->Slider::setColour(Slider::backgroundColourId, Colours::yellow);
  bdSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  bdSlider->setBounds (160, 64, 500, 16);

  rtSlider.reset (new juce::Slider ("Rate"));
  addAndMakeVisible (rtSlider.get());
  rtSlider->setRange (1, 70, 0);
  rtSlider->setValue(DEFAULT_RT);
  rtSlider->setSliderStyle (Slider::LinearHorizontal);
  rtSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  rtSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  rtSlider->setBounds (160, 96, 500, 16);

  mdButton.reset (new juce::ToggleButton ("Invert"));
  addAndMakeVisible (mdButton.get());

  mdButton->setBounds (160, 128, 72, 24);

  fqSlider.reset (new juce::Slider ("LFO freq (Hz)"));
  addAndMakeVisible (fqSlider.get());
  fqSlider->setRange (0.1, 20.0, 0);
  fqSlider->setValue(DEFAULT_FQ);
  fqSlider->setSliderStyle (Slider::LinearHorizontal);
  fqSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  fqSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  fqSlider->setBounds (160, 160, 500, 16);

  amSlider.reset (new juce::Slider ("Mod Amount"));
  addAndMakeVisible (amSlider.get());
  amSlider->setRange (0.0, MAX_RT / 2, 0);
  amSlider->setValue(DEFAULT_AM);
  amSlider->setSliderStyle (Slider::LinearHorizontal);
  amSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  amSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  amSlider->setBounds (160, 192, 500, 16);

  wfSlider.reset (new juce::Slider ("Waveform"));
  addAndMakeVisible (wfSlider.get());
  wfSlider->setRange (0, 4, 1);
  wfSlider->setValue(DEFAULT_WF);
  wfSlider->setSliderStyle (Slider::LinearHorizontal);
  wfSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  wfSlider->setBounds (160, 224, 500, 16);

  dwAttachment.reset(new SliderAttachment(parameters, NAME_DW, *dwSlider));
  bdAttachment.reset(new SliderAttachment(parameters, NAME_BD, *bdSlider));
  rtAttachment.reset(new SliderAttachment(parameters, NAME_RT, *rtSlider));
  mdAttachment.reset(new ButtonAttachment(parameters, NAME_MD, *mdButton));
  fqAttachment.reset(new SliderAttachment(parameters, NAME_FQ, *fqSlider));
  amAttachment.reset(new SliderAttachment(parameters, NAME_AM, *amSlider));
  wfAttachment.reset(new SliderAttachment(parameters, NAME_WF, *wfSlider));

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

  fqLabel.reset (new juce::Label ("LFO freq (Hz)"));
  addAndMakeVisible (fqLabel.get());
  fqLabel->setText("Freq LFO (Hz)", juce::dontSendNotification);
  fqLabel->attachToComponent(fqSlider.get(), true);

  amLabel.reset (new juce::Label ("Mod Amount"));
  addAndMakeVisible (amLabel.get());
  amLabel->setText("Mod Amount", juce::dontSendNotification);
  amLabel->attachToComponent(amSlider.get(), true);

  wfLabel.reset (new juce::Label ("Waveform"));
  addAndMakeVisible (wfLabel.get());
  wfLabel->setText("LFO Shape", juce::dontSendNotification);
  wfLabel->attachToComponent(wfSlider.get(), true);

  setSize (800, 400);

}

MyBitCrushAudioProcessorEditor::~MyBitCrushAudioProcessorEditor()
{
  dwAttachment = nullptr;
  bdAttachment = nullptr;
  rtAttachment = nullptr;
  mdAttachment = nullptr;
  fqAttachment = nullptr;
  amAttachment = nullptr;
  wfAttachment = nullptr;

  //[/Destructor_pre]

  dwSlider = nullptr;
  bdSlider = nullptr;
  rtSlider = nullptr;
  mdButton = nullptr;
  fqSlider = nullptr;
  amSlider = nullptr;
  wfSlider = nullptr;

  dwLabel = nullptr;
  bdLabel = nullptr;
  rtLabel = nullptr;
  fqLabel = nullptr;
  amLabel = nullptr;
  wfLabel = nullptr;
}

//==============================================================================
void MyBitCrushAudioProcessorEditor::paint (juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack); //fillAll = metodo del graphic context
}

void MyBitCrushAudioProcessorEditor::resized()
{
}