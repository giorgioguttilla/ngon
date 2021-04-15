/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PrismVoice.h"
#include "PrismSound.h"
#include <signal.h>


//==============================================================================
PrismizerAudioProcessor::PrismizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       .withInput  ("Sidechain", juce::AudioChannelSet::stereo())
                       ),
params(*this, nullptr, "PARAMETERS", {
    
    std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.0f, 10.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("decay", "Decay", 0.0f, 5.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", 0.0f, 20.0f, 1.0f),
    std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.0f, 20.0f, 0.0f),
    
    std::make_unique<juce::AudioParameterFloat>("smoothing", "Smoothing", 0.0f, 1.0f, 0.1f),
    std::make_unique<juce::AudioParameterFloat>("detune", "Detune", -1.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("spread", "Spread", 0.0f, 1.0f, 0.1f),
    
    std::make_unique<juce::AudioParameterFloat>("vibratoRate", "VibratoRate", 0.1f, 20.0f, 1.0f),
    std::make_unique<juce::AudioParameterFloat>("vibratoDepth", "VibratoDepth", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterBool>("vibratoTrigger", "VibratoTrigger", false),
    
    std::make_unique<juce::AudioParameterFloat>("tremoloRate", "TremoloRate", 0.1f, 20.0f, 1.0f),
    std::make_unique<juce::AudioParameterFloat>("tremoloDepth", "TremoloDepth", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterBool>("tremoloTrigger", "TremoloTrigger", false),
        
    std::make_unique<juce::AudioParameterFloat>("rawVolume", "RawVolume", 0.0f, 1.0f, 1.0f),
    std::make_unique<juce::AudioParameterFloat>("wetVolume", "WetVolume", 0.0f, 1.0f, 1.0f)
    
})

// ^^^ add parameters here
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
    /*
     All necessary classes are instantiated here.
     
     Note that samplesPerBlock is the MAX possible buffer size, not the actual one that
     will be used in processing. We thus instantiate buffers with enough space for
     samplesPerBlock samples but will only do processing on buffer.getNumSamples()
     samples.
     */
    
    //saves sample rate
    sr = sampleRate;
        
    //create new window manager
    wm = new WindowManager(winsize, samplesPerBlock);
    
    //create pitch estimator
    yin = std::make_unique<Yin>(sr, wm->getWindowSize());
    
    //instantiate processbuffer with max possble samples, will be sent to each voice in the preparetoplay method
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
    
    /*
     Block processing is performed in a series of stages:
     
     WINDOWING/ESTIMATION - series of buffers are accumulated and processed at the same time
     to determine pitch. Processing happens every samplesPerBlock/buffer.getNumSamples() calls.
     Each synth voice then gets an update from this analysis
     
     SYNTH RENDERING - synth processing occurs. processBuffer is used to accumulate all
     separate voice outputs for mixin with raw signal. Within each synth voice is where
     pitch shifting occurs. Necessary parameters are applied
     */
    
    //WINDOWING/ESTIMATION
    
    //windowmanager needs to update buffer size if it is less than samplesPerBlock
    if(wm->getBufferSize() != buffer.getNumSamples())
    {
        wm = new WindowManager(wm->getWindowSize(), buffer.getNumSamples());
    }
    
    //accumulates buffers in wm, then performs analysis once window is full
    float* inData = (float*)buffer.getReadPointer (0);

    wm->append(inData);
    
    if (wm->isFull()){
   
        //get estimated pitch from accumulated buffer
        pitchEst = yin->getPitch(&wm->getWindow().at(0));   //converts vector to array ptr

        //Updates hz pitch target in each synth voice
        for (int i = 0; i < synth.getNumVoices(); ++i){

            if (auto voice = dynamic_cast<PrismVoice*>(synth.getVoice(i))){

                voice->setInPitch(pitchEst);

            }

        }
        
    }

    
//    DBG(std::to_string(*params.getRawParameterValue("smoothing")));
//    DBG(std::to_string(*params.getRawParameterValue("tremoloDepth")));
//    DBG(std::to_string(*params.getRawParameterValue("tremoloTrigger")));
//    DBG("---");


    //SYNTH RENDERING
    
    //reset processbuffer for this call
    processBuffer.clear();

    //update voices' ADSR envelopes
    for (int i = 0; i < synth.getNumVoices(); ++i){
        if (auto voice = dynamic_cast<PrismVoice*>(synth.getVoice(i))){
            juce::ADSR::Parameters adsrParams = juce::ADSR::Parameters();

            adsrParams.attack = *params.getRawParameterValue("attack");
            adsrParams.decay = *params.getRawParameterValue("decay");
            adsrParams.sustain = *params.getRawParameterValue("sustain");
            adsrParams.release = *params.getRawParameterValue("release");

            voice->adsr.setParameters(adsrParams);
        }
    }

    //This method triggers all voice process methods, which accumulate their output to the process buffer supplied in prepareToPlay
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());


    //Gain from the sliders is applied to each respective channel
    buffer.applyGain(*params.getRawParameterValue("rawVolume"));
    processBuffer.applyGain(*params.getRawParameterValue("wetVolume"));


    //mono-safe mixin from processBuffer, note that buffer already has raw signal so we are adding not copying
    //and that we are only copying buffer.getNumSamples() samples
    buffer.addFrom(0, 0, (float*)processBuffer.getReadPointer(0), buffer.getNumSamples());
    
    if(buffer.getNumChannels() > 1)
    {
        buffer.addFrom(1, 0, (float*)processBuffer.getReadPointer(1), processBuffer.getNumSamples());
    }

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

//gets closest midi note from hertz value, takes highest note under hertz plus slight bump to avoid fp errors
int PrismizerAudioProcessor::getMidiNoteFromHz (float hz)
{
    if((int)hz == -1)
    {
        return -1;
    }
    float bump = hz/100.0;  //best i can do... might be inaccurate at low frequencies
    return 69 + (12 * log2((hz+bump)/440.0));
}

//rounds supplied freq to closest midi note from provided vector. Vector takes the form of: 0 = c, 1 = c#...
float PrismizerAudioProcessor::roundFreqToNearestNote(float inFreq, std::vector<int> useNotes)
{
    float bestFreq = 0.0;
    float bestDist = 10000.0;
    
    if((int)inFreq == -1)
    {
        return -1;
    }
    
    for(int note : useNotes)
    {
        for (int i = 0; i < 8; i++) {
            float curFreq = juce::MidiMessage::getMidiNoteInHertz(note + (12 * i));
            float curDist = abs(inFreq - curFreq);
            if(curDist < bestDist)
            {
                bestFreq = curFreq;
                bestDist = curDist;
            }
        }
    }
    
    return bestFreq;
}

