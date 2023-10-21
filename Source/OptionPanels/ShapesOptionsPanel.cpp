//
// Created by arden on 8/29/23.
//

#include "ShapesOptionsPanel.h"

ShapesOptionsPanel::ShapesOptionsPanel(TuxConstants::TuxInternalParameters& p)
    : OptionsPanel(p, "Shapes"),
      shapeSelector(&(p.shapes), icons),
      originSelector(&(p.shapeOrigin), originIcons)
{
    addAndMakeVisible(shapeSelector);
    addAndMakeVisible(originSelector);
}

ShapesOptionsPanel::~ShapesOptionsPanel()
{

}

void ShapesOptionsPanel::paint (juce::Graphics& g)
{

}
void ShapesOptionsPanel::resized()
{
    titlePanel.setBounds(getLocalBounds().withHeight(40));
    shapeSelector.setBounds(getLocalBounds().withTrimmedTop(40).withTrimmedBottom(TuxConstants::buttonHeight));
    originSelector.setBounds(getLocalBounds().withHeight(TuxConstants::buttonHeight).withBottomY(getLocalBounds().getBottom()));
}
