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
    attack.slider.setRange(0.0, 10.0);
    attack.slider.setSkewFactor(0.45);
    attack.slider.setValue(0.0);
    
    decay.setText("Decay");
    decay.slider.setRange(0.0, 5.0);
    decay.slider.setSkewFactor(0.45);
    attack.slider.setValue(0.0);
    
    sustain.setText("Sustain");
    sustain.slider.setRange(0.0, 20.0);
    sustain.slider.setSkewFactor(0.45);
    attack.slider.setValue(1.0);
    
    release.setText("Release");
    release.slider.setRange(0.0, 20.0);
    release.slider.setSkewFactor(0.45);
    attack.slider.setValue(0.0);
    
    for (int i = 0; i < 4; i++) {
        adsr[i]->slider.textFromValueFunction = [](double value)
        {
            if (value >= 1.0)
            {
                return juce::String(value, 2) + "s";
            }
            else
            {
                double nv = value * 1000;
                return juce::String((int)nv) + "ms";
            }
        };
        
        adsr[i]->slider.updateText();
        
        addAndMakeVisible(adsr[i]);
        adsr[i]->setSize(100, 100);
    }
    
    
    
}

AdsrControls::~AdsrControls()
{
}

void AdsrControls::paint (juce::Graphics& g)
{

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
