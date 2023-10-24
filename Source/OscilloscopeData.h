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
    void resize(int period);
    void insertSamples(const float* samples, int numSamples);
    const std::vector<float>* const getSamples() const;
private:
    std::vector<float> samples;
    int position;
};

#endif //TUXPAINTVST_OSCILLOSCOPEDATA_H
