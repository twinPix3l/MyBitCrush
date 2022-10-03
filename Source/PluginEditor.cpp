
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
	dwSlider->setSliderStyle (Slider::LinearHorizontal);
  	dwSlider->Slider::setColour(Slider::trackColourId, Colours::darkred);
  	dwSlider->Slider::setColour(Slider::backgroundColourId, Colours::darkseagreen);
  
  	dwSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

  	dwSlider->setBounds (150, 54, 500, 16);

  	bdSlider.reset (new juce::Slider ("BitDepth"));
  	addAndMakeVisible (bdSlider.get());
  	bdSlider->setRange (1, 32, 1);
  	bdSlider->setValue(DEFAULT_BD);
  	bdSlider->setSliderStyle (Slider::LinearHorizontal);
  	bdSlider->Slider::setColour(Slider::backgroundColourId, Colours::yellow);
  	bdSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	bdSlider->setBounds (150, 86, 500, 16);

  	rtSlider.reset (new juce::Slider ("Rate"));
  	addAndMakeVisible (rtSlider.get());
  	rtSlider->setRange (1, 70, 1);
  	rtSlider->setValue(DEFAULT_RT);
  	rtSlider->setSliderStyle (Slider::LinearHorizontal);
  	rtSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  	rtSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	rtSlider->setBounds (150, 118, 500, 16);

  	mdButton.reset (new juce::ToggleButton ("Invert"));
  	mdButton->setColour(0x1000281, Colours::black);
	addAndMakeVisible (mdButton.get());

  	mdButton->setBounds (545, 146, 72, 24);

  	fqSlider.reset (new juce::Slider ("LFO freq (Hz)"));
  	addAndMakeVisible (fqSlider.get());
  	fqSlider->setRange (0.1, 20.0, 0);
  	fqSlider->setValue(DEFAULT_FQ);
  	fqSlider->setSliderStyle (Slider::LinearHorizontal);
  	fqSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  	fqSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	fqSlider->setBounds (150, 182, 500, 16);

  	amSlider.reset (new juce::Slider ("Mod Amount"));
  	addAndMakeVisible (amSlider.get());
  	amSlider->setRange (0.0, MAX_RT / 2, 0);
  	amSlider->setValue(DEFAULT_AM);
  	amSlider->setSliderStyle (Slider::LinearHorizontal);
  	amSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  	amSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	amSlider->setBounds (150, 214, 500, 16);

  	wfSlider.reset (new juce::Slider ("Waveform"));
  	addAndMakeVisible (wfSlider.get());
  	wfSlider->setRange (0, 4, 1);
  	wfSlider->setValue(DEFAULT_WF);
  	wfSlider->setSliderStyle (Slider::LinearHorizontal);
  	wfSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	wfSlider->setBounds (150, 246, 500, 16);

  	gpSlider.reset (new juce::Slider ("Volume"));
  	addAndMakeVisible (gpSlider.get());
  	gpSlider->setRange (0.0f, 1.0f, 0);
  	gpSlider->setValue(DEFAULT_GP);
  	gpSlider->setSliderStyle (Slider::LinearVertical);
  	gpSlider->Slider::setColour(Slider::trackColourId, Colours::green);
  	gpSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);

  	gpSlider->setBounds (685, 50, 48, 240);

  	dwAttachment.reset(new SliderAttachment(parameters, NAME_DW, *dwSlider));
  	bdAttachment.reset(new SliderAttachment(parameters, NAME_BD, *bdSlider));
  	rtAttachment.reset(new SliderAttachment(parameters, NAME_RT, *rtSlider));
  	mdAttachment.reset(new ButtonAttachment(parameters, NAME_MD, *mdButton));
  	fqAttachment.reset(new SliderAttachment(parameters, NAME_FQ, *fqSlider));
  	amAttachment.reset(new SliderAttachment(parameters, NAME_AM, *amSlider));
  	wfAttachment.reset(new SliderAttachment(parameters, NAME_WF, *wfSlider));
  	gpAttachment.reset(new SliderAttachment(parameters, NAME_GP, *gpSlider));

  	dwLabel.reset (new juce::Label ("Dry/Wet"));
  	addAndMakeVisible (dwLabel.get());
  	dwLabel->setText("Dry/Wet", juce::dontSendNotification);
  	dwLabel->attachToComponent(dwSlider.get(), true);
	dwLabel->setColour(0x1000281, Colours::black);

  	bdLabel.reset (new juce::Label ("Bit Depth"));
  	addAndMakeVisible (bdLabel.get());
  	bdLabel->setText("Bit Depth", juce::dontSendNotification);
  	bdLabel->attachToComponent(bdSlider.get(), true);
	bdLabel->setColour(0x1000281, Colours::black);

  	rtLabel.reset (new juce::Label ("Rate"));
  	addAndMakeVisible (rtLabel.get());
  	rtLabel->setText("Rate", juce::dontSendNotification);
  	rtLabel->attachToComponent(rtSlider.get(), true);
	rtLabel->setColour(0x1000281, Colours::black);

  	fqLabel.reset (new juce::Label ("LFO freq (Hz)"));
  	addAndMakeVisible (fqLabel.get());
  	fqLabel->setText("Freq LFO (Hz)", juce::dontSendNotification);
  	fqLabel->attachToComponent(fqSlider.get(), true);
	fqLabel->setColour(0x1000281, Colours::black);

  	amLabel.reset (new juce::Label ("Mod Amount"));
  	addAndMakeVisible (amLabel.get());
  	amLabel->setText("Mod Amount", juce::dontSendNotification);
  	amLabel->attachToComponent(amSlider.get(), true);
	amLabel->setColour(0x1000281, Colours::black);

  	wfLabel.reset (new juce::Label ("Waveform"));
  	addAndMakeVisible (wfLabel.get());
  	wfLabel->setText("LFO Shape", juce::dontSendNotification);
  	wfLabel->attachToComponent(wfSlider.get(), true);
	wfLabel->setColour(0x1000281, Colours::black);

  	gpLabel.reset (new juce::Label ("Volume"));
  	addAndMakeVisible (gpLabel.get());
  	gpLabel->setText("Volume", juce::dontSendNotification);
  	gpLabel->attachToComponent(gpSlider.get(), false);

  	setSize (768, 304);
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
  	gpAttachment = nullptr;

  	//[/Destructor_pre]

  	dwSlider = nullptr;
  	bdSlider = nullptr;
  	rtSlider = nullptr;
  	mdButton = nullptr;
  	fqSlider = nullptr;
  	amSlider = nullptr;
  	wfSlider = nullptr;
  	gpSlider = nullptr;

  	dwLabel = nullptr;
  	bdLabel = nullptr;
  	rtLabel = nullptr;
  	fqLabel = nullptr;
  	amLabel = nullptr;
  	wfLabel = nullptr;
  	gpLabel = nullptr;

}

//==============================================================================
void MyBitCrushAudioProcessorEditor::paint (juce::Graphics& g)
{
  	//g.fillAll(juce::Colours::transparentBlack); //fillAll = metodo del graphic context

    	{
        	int x = 0, y = 0, width = 768, height = 304;
        	juce::Colour fillColour1 = Colours::black, fillColour2 = Colours::silver/*juce::Colour (0xff250885)*/;
		g.setGradientFill (juce::ColourGradient (fillColour1, 340.0f - 0.0f + x, 240.0f - 0.0f + y,
                                                 	 fillColour2, 40.0f - 0.0f + x, 0.0f - 0.0f + y,
                                                 	 false));
        	g.fillRect (x, y, width, height);
    	}
	
	{
		g.setFont (40.0f);
		g.setColour (juce::Colours::silver);
		g.drawText ("__________________", getLocalBounds(), juce::Justification::topLeft, true);
		g.setColour (juce::Colours::blueviolet);
		g.drawText ("Bitle", getLocalBounds(), juce::Justification::centredTop, true);
		g.setColour (juce::Colours::silver);
		g.drawText ("________Juce", getLocalBounds(), juce::Justification::centredTop, true);
    	}

	{
		g.setColour(Colours::black);
		g.setOpacity(0.25);
		g.drawImageAt(btj, 0, 0, false);
		
		//g.setTiledImageFill(btj, 0, 0, 0.9);
	}
}

void MyBitCrushAudioProcessorEditor::resized()
{
}