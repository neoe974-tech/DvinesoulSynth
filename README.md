# DvinesoulSynth

Clean-room reconstruction starter for the DvinesoulSynth project.

> This repository is a rebuilt foundation, not a claim that the original lost source has been recovered.

## Current foundation

- JUCE-based C++17 project
- Standalone application target
- VST3 target
- MIDI input
- 8-voice polyphonic synthesiser
- Sine oscillator
- ADSR envelope
- Basic dark metallic-style editor foundation

## Requirements

- Linux/Kali
- C++17 compiler
- CMake
- Ninja
- JUCE

## JUCE

JUCE is intentionally not bundled. The current development machine has a checkout at `~/JUCE`.

From the home directory:

    cd ~
    ln -s ~/JUCE DvinesoulSynth/JUCE

If the link already exists, leave it unchanged.

## Build

    cd ~/DvinesoulSynth
    cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
    cmake --build build -j2

The first build is intended to validate the reconstructed foundation. Additional synth features, presets, modulation, effects, GUI controls and sound-design features can be added incrementally after the base build is confirmed.
