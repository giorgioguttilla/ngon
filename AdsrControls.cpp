/*
  ==============================================================================

    AdsrControls.cpp
    Created: 4 Mar 2021 9:18:12pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrControls.h"

//==============================================================================
AdsrControls::AdsrControls()
{
    
    setSize(200, 200);
    
    attack.setText("Attack");
    decay.setText("Decay");
    sustain.setText("Sustain");
    release.setText("Release");
    
    for (int i = 0; i < 4; i++) {
        addAndMakeVisible(adsr[i]);
        adsr[i]->setSize(100, 100);
    }
    
    
    
}

AdsrControls::~AdsrControls()
{
}

void AdsrControls::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);

}

void AdsrControls::resized()
{
    attack.setBounds(0, 0, getWidth()/2, getHeight()/2);
    decay.setBounds(getWidth()/2, 0, getWidth()/2, getHeight()/2);
    sustain.setBounds(0, getHeight()/2, getWidth()/2, getHeight()/2);
    release.setBounds(getWidth()/2, getHeight()/2, getWidth()/2, getHeight()/2);
}
