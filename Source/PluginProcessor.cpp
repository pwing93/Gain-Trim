/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTrimPlugInAudioProcessor::GainTrimPlugInAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(gain = new AudioParameterFloat("gain", "Gain", 0.0, 1.0, 0.0));
}

GainTrimPlugInAudioProcessor::~GainTrimPlugInAudioProcessor()
{
}

//==============================================================================
const String GainTrimPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainTrimPlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainTrimPlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainTrimPlugInAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainTrimPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainTrimPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainTrimPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainTrimPlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String GainTrimPlugInAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainTrimPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GainTrimPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GainTrimPlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainTrimPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GainTrimPlugInAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    auto* channeldataL = buffer.getWritePointer(0);
    auto* channeldataR = buffer.getWritePointer(1);
    
    float gSlider = gain->get();
    
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        auto inputL = channeldataL[i];
        auto inputR = channeldataR[i];
        
        inputL = inputL * gSlider;
        inputR = inputR * gSlider;
        
        channeldataL[i] = inputL;
        channeldataR[i] = inputR;
    }
}

//==============================================================================
bool GainTrimPlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainTrimPlugInAudioProcessor::createEditor()
{
    //return new GainTrimPlugInAudioProcessorEditor (*this);
    return new GenericAudioProcessorEditor(this);
}

//==============================================================================
void GainTrimPlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainTrimPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainTrimPlugInAudioProcessor();
}
