#pragma once
#include <JuceHeader.h>

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int) override {}
    void controllerMoved (int, int) override {}

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void renderNextBlock (juce::AudioBuffer<float>&, int startSample, int numSamples) override;

private:
    juce::dsp::Oscillator<float> oscillator;
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    float level = 0.0f;
};
