#include "PluginProcessor.h"
#include "PluginEditor.h"

DvinesoulSynthAudioProcessor::DvinesoulSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true))
#endif
{
    for (int i = 0; i < 8; ++i)
        synth.addVoice (new SynthVoice());

    synth.addSound (new SynthSound());
}

void DvinesoulSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);

    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* voice = dynamic_cast<SynthVoice*> (synth.getVoice (i)))
            voice->prepareToPlay (sampleRate, samplesPerBlock);
}

void DvinesoulSynthAudioProcessor::releaseResources()
{
}

bool DvinesoulSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void DvinesoulSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                                juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();
    synth.renderNextBlock (buffer, midi, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* DvinesoulSynthAudioProcessor::createEditor()
{
    return new DvinesoulSynthAudioProcessorEditor (*this);
}
