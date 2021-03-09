/*
  ==============================================================================

    TunerKeyboard.h
    Created: 5 Mar 2021 10:37:57am
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <algorithm>

#include "StickyKeyboard.h"
#include "TaggedKey.h"

//==============================================================================
/*
*/

class TunerKeyboard  : public juce::Component, public juce::Button::Listener
{
public:
        
    TaggedKey *whiteKeys [7];
    TaggedKey *blackKeys [5];
    std::vector<TaggedKey *> keys;
    
    
    TunerKeyboard()
    {
        
        setSize(200, 100);
        
        float wKeyWidth = getWidth()/7;
        float bKeyWidth = getWidth()/14;
        float bKeyHeight = getHeight() * 0.6;
        float bKeyOffset = wKeyWidth - (bKeyWidth/2);
        
        for (int i = 0; i < 7; i++)
        {
            
            whiteKeys[i] = new TaggedKey(i <= 2 ? 2 * i : (2 * i) - 1);   //memory leak?
            
            whiteKeys[i]->setBounds(i * wKeyWidth, 0, wKeyWidth, getHeight());
            
            addAndMakeVisible(whiteKeys[i]);
            
            whiteKeys[i]->addListener(this);
            
            DBG(whiteKeys[i]->getNote());
            
            keys.push_back(whiteKeys[i]);
            
        }
        
        for (int i = 0; i < 5; i++)
        {
                        
            blackKeys[i] = new TaggedKey(i < 2 ? (2 * i) + 1 : 2 * (i + 1));    //memory leak?
            
            int skip = i >= 2 ? 1 : 0;
            
            blackKeys[i]->setBounds((i + skip) * wKeyWidth + bKeyOffset, 0, bKeyWidth, bKeyHeight);
            
            addAndMakeVisible(blackKeys[i]);
            
            blackKeys[i]->addListener(this);
            
            DBG(blackKeys[i]->getNote());
            
            keys.push_back(blackKeys[i]);
        }
        
        //sorts keys array for easy access
        std::sort(keys.begin(), keys.end(), [](TaggedKey *a, TaggedKey *b)
        {
            return a->getNote() < b->getNote();
        });

    }

    ~TunerKeyboard() override
    {
        for (int i = 0; i < 7; i++) {
            delete whiteKeys[i];
        }
        for (int i = 0; i < 5; i++) {
            delete blackKeys[i];
        }
    }

    void paint (juce::Graphics& g) override
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
        g.drawText ("TunerKeyboard", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
    std::vector<TaggedKey *> getKeysDown()
    {
        return keysDown;
    }
    
    std::vector<int> getValidNotes()
    {
        std::vector<int> notes {0,1,2,3,4,5,6,7,8,9,10,11};
        
        for (auto key : keysDown) {
            notes.erase(std::remove(notes.begin(), notes.end(), key->getNote()));
        }
        
        return notes;
    }
    
    //sets target note for gui, if n = -1 then unset all
    void setTarget(int n)
    {
        for(auto key : keys)
        {
            key->setIsTarget(false);
        }
        
        if(n == -1)
        {
            repaint();
            return;
        }
        
        if(n > 11 || n < 0) return;
        
        keys.at(n)->setIsTarget(true);
        
        repaint();
    }

private:
    
    std::vector<TaggedKey *> keysDown;
    
    void buttonClicked(juce::Button *button) override
    {
        auto k = dynamic_cast<TaggedKey *>(button);
        
        if(k == nullptr) return;
        
        //insert key if pressed down. otherwise remove it from vector
        if(k->getToggleState())
        {
            keysDown.push_back(k);
        }
        else
        {
            for(TaggedKey *currentKeys : keysDown)
            {
                if(currentKeys->getNote() == k->getNote()) keysDown.erase(std::remove(keysDown.begin(), keysDown.end(), currentKeys));
            }
        }
        
        //sorts keys array for easy access
        std::sort(keysDown.begin(), keysDown.end(), [](TaggedKey *a, TaggedKey *b)
        {
            return a->getNote() < b->getNote();
        });
        
        //change color of component
        k->repaint();
        
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TunerKeyboard)
};
