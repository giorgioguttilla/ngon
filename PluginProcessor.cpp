/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "smbPitchShift.cpp"

#include "PrismVoice.h"
#include "PrismSound.h"



//==============================================================================
PrismizerAudioProcessor::PrismizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    synth.addSound(new PrismSound());
    for (int i = 0; i < 2; i++){
        synth.addVoice(new PrismVoice());
    }
}

PrismizerAudioProcessor::~PrismizerAudioProcessor()
{
    if (wm != nullptr) delete wm;
}

//==============================================================================
const juce::String PrismizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PrismizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PrismizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PrismizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PrismizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PrismizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PrismizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PrismizerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PrismizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void PrismizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PrismizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    sr = sampleRate;
    
    //create new window manager
    wm = new WindowManager(winsize, samplesPerBlock);
    wm->clearWindow();
    
    //instantiate processbuffer properly, will be sent to each voice in the preparetoplay method 
    processBuffer.setSize(2, samplesPerBlock);
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if(auto voice = dynamic_cast<PrismVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels(), &processBuffer);
        }
    }
    
}

void PrismizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PrismizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void PrismizerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //appends in buffer to list of previous buffers, then performs analysis once window is full
    
    float* inData = (float*)buffer.getReadPointer (0);
    
    wm->append(inData);
    
    if (wm->isFull()){
        
        Yin yin = Yin(sr, wm->getWindowSize()); //could probably be more efficient, might lead to mem leak
        
        pitchEst = yin.getPitch(wm->getWindow());
        
        //Updates raw pitch target in each synth voice
        
        for (int i = 0; i < synth.getNumVoices(); ++i){
            
            if (auto voice = dynamic_cast<PrismVoice*>(synth.getVoice(i))){
                
                voice->setInPitch(pitchEst);
                
            }
        
        }
        
    }

    
    
    
    
    //SYNTH RENDERING --- copies buffer to processBlock first, then does rendering on processBlock and recombine with buffer after based on wet/dry amount
    processBuffer.clear();
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    buffer.applyGain(rawGain);
    processBuffer.applyGain(modGain);
    
    buffer.addFrom(0, 0, (float*)processBuffer.getReadPointer(0), processBuffer.getNumSamples());
    buffer.addFrom(1, 0, (float*)processBuffer.getReadPointer(1), processBuffer.getNumSamples());

    
    
//    buffer.clear();
//    
//    for (int i = 0; i < synth.getNumVoices(); ++i){
//
//        if (auto voice = dynamic_cast<PrismVoice*>(synth.getVoice(i))){
//            
//            buffer.addFrom(0, 0, voice->getWriteBuffer()->getReadPointer(0), buffer.getNumSamples());
//
//        }
//
//    }
    
    //buffer.applyGain(1/synth.getNumVoices());
    
    DBG("-------");
    
}

//==============================================================================
bool PrismizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PrismizerAudioProcessor::createEditor()
{
    return new PrismizerAudioProcessorEditor (*this);
}

//==============================================================================
void PrismizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PrismizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PrismizerAudioProcessor();
}


int PrismizerAudioProcessor::getMidiNoteFromHz (float hz){
    return log(hz/440.0)/log(2) * 12 + 69;
}
