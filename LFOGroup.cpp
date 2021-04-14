/*
  ==============================================================================

    LFOGroup.cpp
    Created: 13 Apr 2021 8:47:03am
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOGroup.h"

//==============================================================================
LFOGroup::LFOGroup()
{
    addAndMakeVisible(rateSlider);
    addAndMakeVisible(depthSlider);
    addAndMakeVisible(triggerButton);
    addAndMakeVisible(label);
    
    setSize(200, 200);
    
    rateSlider.setText("Rate");
    rateSlider.slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    rateSlider.slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    rateSlider.slider.setTextBoxIsEditable(true);
    rateSlider.slider.setRange(0.01, 20);
//    rateSlider.slider.setSkewFactor(15);
    rateSlider.slider.setValue(1);
    
    depthSlider.setText("Depth");
    depthSlider.slider.setSliderStyle(juce::Slider::LinearVertical);
    depthSlider.slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    depthSlider.slider.setTextBoxIsEditable(true);
    rateSlider.slider.setRange(0, 1);
    rateSlider.slider.setValue(0);
    
    triggerButton.setEnabled(true);
    
    label.setText("TEST", juce::NotificationType::dontSendNotification);
    
}

LFOGroup::~LFOGroup()
{
}

void LFOGroup::paint (juce::Graphics& g)
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

void LFOGroup::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    label.setBounds(0, getHeight()/2, 50, 30);
    rateSlider.setBounds(50, 0, getWidth()/2, getHeight()/2);
    depthSlider.setBounds(50+getWidth()/2, 0, 50, getHeight());
    triggerButton.setBounds(0, getHeight() - getHeight()/4, 30, 30);
    
}

void LFOGroup::setText(const std::string text)
{
    label.setText(text, juce::dontSendNotification);
}
