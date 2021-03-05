/*
  ==============================================================================

    FollowerControl.cpp
    Created: 4 Mar 2021 6:58:10pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#include "FollowerControl.h"

FollowerControl::FollowerControl()
{
    
    addAndMakeVisible(pitchLabel);
    addAndMakeVisible(pitchSlider);
    addAndMakeVisible(label);
    addAndMakeVisible(toggle);
    
    setSize(200, 100);
    
    pitchSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
    pitchSlider.setTextBoxIsEditable(true);

    pitchSlider.setNormalisableRange(juce::NormalisableRange<double>(-12, 12, 1.0));
    pitchSlider.setValue(0.0);

    pitchSlider.textFromValueFunction = [](double value)
    {
        return juce::String(value, 0);
    };
    
    pitchLabel.setText("Semitones", juce::dontSendNotification);
    pitchLabel.attachToComponent(&pitchSlider, false);
    pitchLabel.setColour(juce::Label::textColourId, juce::Colours::skyblue);
    pitchLabel.setJustificationType (juce::Justification::centred);
    
    
    label.setText("Follower", juce::dontSendNotification);
    label.attachToComponent(&pitchSlider, true);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    label.setJustificationType (juce::Justification::centred);
    
}

FollowerControl::~FollowerControl()
{
    
}

void FollowerControl::resized()
{
    label.setBounds(0, 0, getWidth()/2, getHeight());
    toggle.setBounds(label.getWidth(), 0, getWidth()/6, getHeight());
    pitchLabel.setBounds(label.getWidth()+toggle.getWidth(), 0, getWidth()/3, getHeight()/3);
    pitchSlider.setBounds(label.getWidth()+toggle.getWidth(), pitchLabel.getHeight(), getWidth()/3, (2*getHeight())/3);
}


void FollowerControl::setText(const std::string text)
{
    label.setText(text, juce::dontSendNotification);
}
