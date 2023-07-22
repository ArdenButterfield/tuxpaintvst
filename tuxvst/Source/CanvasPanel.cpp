//
// Created by arden on 7/22/23.
//

#include "CanvasPanel.h"

CanvasPanel::CanvasPanel() {

}

CanvasPanel::~CanvasPanel() {

}
void CanvasPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::red);
    g.fillAll();
}
void CanvasPanel::resized() {

}
