//
// Created by arden on 9/6/23.
//

#include "MagicOptionPanel.h"

MagicOptionPanel::MagicOptionPanel(TuxConstants::TuxInternalParameters& p)
    : OptionsPanel(p, "Magic"), parameters(p)
{

    for (int type = 0; type < Magic::NUM_MAGIC_TYPES; ++type) {
        auto& effects = Magic::magicEffects[type];
        for (auto& effect : effects) {
            icons[type].push_back(effect->getIcon());
        }
        // TODO:
        //  buttonSelectors.add(new ButtonSelector(p, Magic::magic_ids[type], icons[type]));
    }
    currentButtonSelector = 0;
    parameters.magicType.addListener(this);
    addAndMakeVisible(buttonSelectors[currentButtonSelector]);
}

MagicOptionPanel::~MagicOptionPanel()
{
    parameters.magicType.removeListener(this);

    buttonSelectors.clear(true);
}

void MagicOptionPanel::paint (juce::Graphics& g)
{
    g.drawImageAt (buttonNav, prevButtonBounds.getX(), prevButtonBounds.getY());
    g.drawImageAt (buttonNav, nextButtonBounds.getX(), nextButtonBounds.getY());
    auto prevInnerBounds = prevButtonBounds.withSizeKeepingCentre (prevIcon.getWidth(), prevIcon.getHeight());
    auto nextInnerBounds = nextButtonBounds.withSizeKeepingCentre (nextIcon.getWidth(), nextIcon.getHeight());
    g.drawImageAt (prevIcon, prevInnerBounds.getX(), prevInnerBounds.getY());
    g.drawImageAt (nextIcon, nextInnerBounds.getX(), nextInnerBounds.getY());

/*
 * TODO:
    auto currentMagicEffect = Magic::getCurrentMagicEffect(parameters);
    auto mode = currentMagicEffect->getMode();
    auto availableModes = currentMagicEffect->getAvailableModes();

    const juce::Image* fullscreenIm;
    if (!(availableModes & Magic::MODE_FULLSCREEN)) {
        fullscreenIm = &buttonOffBackground;
    } else if (mode == Magic::MODE_FULLSCREEN) {
        fullscreenIm = &buttonDownBackground;
    } else {
        fullscreenIm = &buttonUpBackground;
    }
    g.drawImageAt(*fullscreenIm, magicFullscreenButtonBounds.getX(), magicFullscreenButtonBounds.getY());

    const juce::Image* paintIm;
    auto paintModes = (Magic::MODE_ONECLICK | Magic::MODE_PAINT | Magic::MODE_PAINT_WITH_PREVIEW);
    if (!(availableModes & paintModes)) {
        paintIm = &buttonOffBackground;
    } else if (mode & paintModes) {
        paintIm = &buttonDownBackground;
    } else {
        paintIm = &buttonUpBackground;
    }
    g.drawImageAt(*paintIm, magicPaintButtonBounds.getX(), magicPaintButtonBounds.getY());

    g.drawImageAt(
        magicFullscreenIcon,
        magicFullscreenButtonBounds.getCentreX() - magicFullscreenIcon.getWidth() / 2,
        magicFullscreenButtonBounds.getCentreY() - magicFullscreenIcon.getHeight() / 2);
    g.drawImageAt(
        magicPaintIcon,
        magicPaintButtonBounds.getCentreX() - magicPaintIcon.getWidth() / 2,
        magicPaintButtonBounds.getCentreY() - magicPaintIcon.getHeight() / 2);
    */
}

void MagicOptionPanel::resized()
{
    titlePanel.setBounds(getLocalBounds().withHeight(40));
    for (auto& selector : buttonSelectors) {
        selector->setBounds(getLocalBounds().withTrimmedTop(40).withTrimmedBottom(TuxConstants::buttonHeight * 2));
    }
    auto optionArea = getLocalBounds().withHeight(TuxConstants::buttonHeight).withBottomY(getBottom());
    auto navArea = getLocalBounds()
                       .withHeight(TuxConstants::buttonHeight)
                       .withBottomY(getBottom() - TuxConstants::buttonHeight);
    prevButtonBounds = navArea.withTrimmedRight(TuxConstants::buttonWidth);
    nextButtonBounds = navArea.withTrimmedLeft(TuxConstants::buttonWidth);

    magicPaintButtonBounds = optionArea.withTrimmedRight(TuxConstants::buttonWidth);
    magicFullscreenButtonBounds = optionArea.withTrimmedLeft(TuxConstants::buttonWidth);
}

void MagicOptionPanel::mouseDown (const juce::MouseEvent& event)
{
/* TODO:
 * if (prevButtonBounds.contains(event.position.roundToInt())) {
        setMagicPane(currentButtonSelector - 1);
        auto p = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype")));
        *p = currentButtonSelector;
    } else if (nextButtonBounds.contains(event.position.roundToInt())) {
        setMagicPane(currentButtonSelector - 1);
        auto p = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype")));
        *p = currentButtonSelector;
    } else if (magicPaintButtonBounds.contains(event.position.roundToInt())) {
        auto currentMagicEffect = Magic::getCurrentMagicEffect(parameters);
        auto availableModes = currentMagicEffect->getAvailableModes();
        if (availableModes & Magic::MODE_ONECLICK) {
            currentMagicEffect->setMode(Magic::MODE_ONECLICK);
        } else if (availableModes & Magic::MODE_PAINT) {
            currentMagicEffect->setMode(Magic::MODE_PAINT);
        } else if (availableModes & Magic::MODE_PAINT_WITH_PREVIEW) {
            currentMagicEffect->setMode(Magic::MODE_PAINT_WITH_PREVIEW);
        }
        repaint();
    } else if (magicFullscreenButtonBounds.contains(event.position.roundToInt())) {
        auto currentMagicEffect = Magic::getCurrentMagicEffect(parameters);
        auto availableModes = currentMagicEffect->getAvailableModes();
        if (availableModes & Magic::MODE_FULLSCREEN) {
            currentMagicEffect->setMode(Magic::MODE_FULLSCREEN);
        }
        repaint();
    }*/
}

void MagicOptionPanel::parameterValueChanged (int parameterIndex, float newValue)
{
    // setMagicPane(dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype"))->getIndex());
}

void MagicOptionPanel::setMagicPane (int index)
{
    if (index == currentButtonSelector) {
        return;
    }
    removeChildComponent(buttonSelectors[currentButtonSelector]);
    index += buttonSelectors.size();
    index %= buttonSelectors.size();
    currentButtonSelector = index;
    addAndMakeVisible(buttonSelectors[currentButtonSelector]);
    repaint();
}
