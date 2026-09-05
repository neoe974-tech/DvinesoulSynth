cmake_minimum_required(VERSION 3.22)
project(DvinesoulSynth VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(JUCE)

juce_add_plugin(DvinesoulSynth
    COMPANY_NAME "Dvinesoul"
    PRODUCT_NAME "DvinesoulSynth"
    PLUGIN_MANUFACTURER_CODE Dvin
    PLUGIN_CODE DSyn
    FORMATS Standalone VST3
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
)

juce_generate_juce_header(DvinesoulSynth)

target_sources(DvinesoulSynth PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/SynthVoice.cpp
    Source/SynthVoice.h
    Source/SynthSound.cpp
    Source/SynthSound.h
)

target_compile_definitions(DvinesoulSynth PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1
)

target_link_libraries(DvinesoulSynth PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)
