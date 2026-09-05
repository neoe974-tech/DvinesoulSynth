#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class DvinesoulSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit DvinesoulSynthAudioProcessorEditor (DvinesoulSynthAudioProcessor&);
    ~DvinesoulSynthAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DvinesoulSynthAudioProcessor& processor;
    juce::Label title;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DvinesoulSynthAudioProcessorEditor)
};
