//
// Created by arden on 10/16/23.
//

#ifndef TUXPAINTVST_TUXSYNTHSOUND_H
#define TUXPAINTVST_TUXSYNTHSOUND_H

#include <juce_audio_basics/juce_audio_basics.h>

class TuxSynthSound : public juce::SynthesiserSound
{
public:
    TuxSynthSound() {}

    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }

};

#endif //TUXPAINTVST_TUXSYNTHSOUND_H
