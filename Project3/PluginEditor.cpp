/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AudioFilterAudioProcessorEditor::AudioFilterAudioProcessorEditor (AudioFilterAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter),
	cutoffLabel("", "Cutoff Amplitude:"),
	cutoffSlider("cutoff")
{
    // This is where our plugin's editor size is set.
    //setSize (400, 300);

	addAndMakeVisible(cutoffSlider);
	cutoffSlider.setSliderStyle(Slider::Rotary);
	cutoffSlider.addListener(this);
	cutoffSlider.setRange(0.0, 1.0, 0.01);

	cutoffLabel.attachToComponent(&cutoffSlider, false);
	cutoffLabel.setFont(Font(11.0f));

	// add the triangular resizer component for the bottom-right of the UI
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(150, 150, 800, 300);

	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(ownerFilter->lastUIWidth,
		ownerFilter->lastUIHeight);
}

AudioFilterAudioProcessorEditor::~AudioFilterAudioProcessorEditor()
{
}

//==============================================================================
void AudioFilterAudioProcessorEditor::paint(Graphics& g)
{
	g.setGradientFill(ColourGradient(Colours::white, 0, 0,
		Colours::grey, 0, (float)getHeight(), false));
	g.fillAll();
	cutoffSlider.setBounds(270, 60, 120, 40);
}

void AudioFilterAudioProcessorEditor::resized()
{
	cutoffSlider.setBounds(270, 60, 120, 40);

	getProcessor()->lastUIWidth = getWidth();
	getProcessor()->lastUIHeight = getHeight();
}

void AudioFilterAudioProcessorEditor::timerCallback()
{
	AudioFilterAudioProcessor* ourProcessor = getProcessor();

	cutoffSlider.setValue(ourProcessor->cutoff, dontSendNotification);

}

// This is our Slider::Listener callback, when the user drags a slider.
void AudioFilterAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &cutoffSlider)
	{
		getProcessor()->setParameterNotifyingHost(AudioFilterAudioProcessor::cutoffParam,
			(float)cutoffSlider.getValue());
	}
}