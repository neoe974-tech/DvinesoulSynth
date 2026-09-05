#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity,
                            juce::SynthesiserSound*, int)
{
    const auto frequency = (float) juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    level = velocity;
    oscillator.setFrequency (frequency);
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    juce::ignoreUnused (velocity);

    if (allowTailOff)
        adsr.noteOff();
    else
    {
        adsr.noteOff();
        clearCurrentNote();
    }
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) samplesPerBlock, 1 };

    oscillator.initialise ([] (float x) { return std::sin (x); }, 128);
    oscillator.prepare (spec);

    adsrParams.attack = 0.01f;
    adsrParams.decay = 0.15f;
    adsrParams.sustain = 0.8f;
    adsrParams.release = 0.25f;

    adsr.setSampleRate (sampleRate);
    adsr.setParameters (adsrParams);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& output,
                                  int startSample, int numSamples)
{
    if (! isVoiceActive())
        return;

    juce::AudioBuffer<float> voiceBuffer (1, numSamples);
    voiceBuffer.clear();

    juce::dsp::AudioBlock<float> block (voiceBuffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    oscillator.process (context);

    auto* source = voiceBuffer.getReadPointer (0);
    auto* destination = output.getWritePointer (0, startSample);

    for (int i = 0; i < numSamples; ++i)
        destination[i] += source[i] * level * adsr.getNextSample();

    if (! adsr.isActive())
        clearCurrentNote();

    if (output.getNumChannels() > 1)
        output.addFrom (1, startSample, voiceBuffer, 0, 0, numSamples);
}
