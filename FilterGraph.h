/*
  ==============================================================================

    FilterGraph.h
    Created: 16 Apr 2021 4:19:06pm
    Author:  Giorgio Guttilla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterGraph  : public juce::Component
{
public:
    FilterGraph();
    ~FilterGraph() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
//    void mouseDown(const juce::MouseEvent &event) override;
    
    void setFilterType(int type);

private:
    
    
    juce::Path hpPath;
    juce::Path lpPath;
    juce::Path bpPath;
    
    int filterType = 0; //0 = lp, 1 = bp, 2 = hp
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGraph)
};
