//
// Created by arden on 10/23/23.
//

#ifndef TUXPAINTVST_OSCILLOSCOPEDATA_H
#define TUXPAINTVST_OSCILLOSCOPEDATA_H

#include <vector>

class OscilloscopeData
{
public:
    OscilloscopeData();
    ~OscilloscopeData();
    void resize(float _period);
    void insertSamples(const float* samples, int numSamples);
    std::vector<float>* getSamples();
private:
    std::vector<float> samples;
    float period;
    float position;
    int freshSamplesNeeded;
};

#endif //TUXPAINTVST_OSCILLOSCOPEDATA_H
