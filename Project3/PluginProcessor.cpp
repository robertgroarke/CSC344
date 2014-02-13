/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>

AudioProcessor* JUCE_CALLTYPE createPluginFilter();

const float defaultCutoff = 1.0f;

//==============================================================================
AudioFilterAudioProcessor::AudioFilterAudioProcessor()
{
	cutoff = defaultCutoff;
	lastUIWidth = 400;
	lastUIHeight = 200;
}

AudioFilterAudioProcessor::~AudioFilterAudioProcessor()
{
}

//==============================================================================
const String AudioFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int AudioFilterAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float AudioFilterAudioProcessor::getParameter (int index)
{
    return cutoff;
}

void AudioFilterAudioProcessor::setParameter (int index, float newValue)
{
	
	cutoff = newValue;
}

float AudioFilterAudioProcessor::getParameterDefaultValue(int index)
{
	switch (index)
	{
	case cutoffParam:   return defaultCutoff;
	default:            break;
	}

	return 0.0f;
}

const String AudioFilterAudioProcessor::getParameterName (int index)
{
	switch (index)
	{
	case cutoffParam:   return "cutoff";
	default:            break;
	}

	return String::empty;
}

const String AudioFilterAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String AudioFilterAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String AudioFilterAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool AudioFilterAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool AudioFilterAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool AudioFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioFilterAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double AudioFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioFilterAudioProcessor::getNumPrograms()
{
    return 0;
}

int AudioFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String AudioFilterAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void AudioFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AudioFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AudioFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void AudioFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

		for (int i = 0; i < buffer.getNumSamples(); i++)
		{
			//channelData[i] = atan(channelData[i]);
			if (channelData[i] > cutoff)
				channelData[i] = cutoff;
		}

        // ..do something to the data...
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool AudioFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AudioFilterAudioProcessor::createEditor()
{
    return new AudioFilterAudioProcessorEditor (this);
}

//==============================================================================
void AudioFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AudioFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioFilterAudioProcessor();
}
