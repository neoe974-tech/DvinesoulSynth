#include "PluginEditor.h"

DvinesoulSynthAudioProcessorEditor::DvinesoulSynthAudioProcessorEditor (
    DvinesoulSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (900, 560);

    title.setText ("DVINESOUL SYNTH", juce::dontSendNotification);
    title.setFont (juce::Font (28.0f, juce::Font::bold));
    title.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (title);
}

void DvinesoulSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff101216));

    g.setColour (juce::Colour (0xff20252c));
    g.fillRoundedRectangle (getLocalBounds().toFloat().reduced (18.0f), 14.0f);

    g.setColour (juce::Colour (0xffb9c0c8));
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (18.0f), 14.0f, 1.0f);
}

void DvinesoulSynthAudioProcessorEditor::resized()
{
    title.setBounds (40, 25, getWidth() - 80, 50);
}
