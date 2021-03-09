/*
  ==============================================================================

    TaggedKey.h
    Created: 5 Mar 2021 3:01:45pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TaggedKey  : public juce::ToggleButton
{
public:
    TaggedKey(int _note) : juce::ToggleButton()
    {
        note = _note;
    }

    ~TaggedKey() override
    {
    }
    
    void setNote(int _note)
    {
        note = _note;
    }
    
    int getNote()
    {
        return note;
    }

    void paint (juce::Graphics& g) override
    {
        
        
        if(getToggleState())
        {
            isMouseOver() ? g.fillAll(juce::Colours::darkcyan) : g.fillAll(juce::Colours::darkgrey);
            isTarget ? g.setColour (juce::Colours::darkred) : g.setColour(juce::Colours::black);
        }
        else
        {
            isMouseOver() ? g.fillAll(juce::Colours::lightcyan) : g.fillAll(juce::Colours::white);
            isTarget ? g.setColour (juce::Colours::indianred) : g.setColour(juce::Colours::black);
        }
        
        g.drawRect (getLocalBounds(), 2);   // draw an outline around the component
        
        

    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
    bool getIsTarget()
    {
        return isTarget;
    }
    
    void setIsTarget(bool t)
    {
        isTarget = t;
    }
    
protected:
    int note;
    bool isTarget = false;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TaggedKey)
};
