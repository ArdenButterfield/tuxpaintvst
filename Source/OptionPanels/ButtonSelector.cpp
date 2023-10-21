//
// Created by arden on 8/29/23.
//

#include "ButtonSelector.h"

ButtonSelector::ButtonSelector(juce::AudioParameterChoice* param, const std::vector<juce::Image>& icons)
      : buttonIcons(icons),
      parameterToAttachTo(param)
{

    parameterToAttachTo->addListener(this);
    selectionIndex = parameterToAttachTo->getIndex();
}

ButtonSelector::~ButtonSelector()
{
    parameterToAttachTo->removeListener(this);
}

void ButtonSelector::resized() {
    cols = getWidth() / buttonWidth;
    rows = getHeight() / buttonHeight;
    if (rows == 0 || cols != 2) {
        return;
    }
    if (rows * cols < buttonIcons.size()) {
        numVisibleButtons = (rows - 1) * cols;
        if (selectionIndex < numVisibleButtons) {
            firstDisplayedIcon = 0;
        } else {
            firstDisplayedIcon = selectionIndex - numVisibleButtons;
            if (firstDisplayedIcon % cols) {
                firstDisplayedIcon += 1;
            }
        }
    } else {
        numVisibleButtons = rows * cols;
        firstDisplayedIcon = 0;
    }
}

void ButtonSelector::paint (juce::Graphics& g)
{
    if (numVisibleButtons < buttonIcons.size()) {
        if (firstDisplayedIcon > 0) {
            g.drawImageAt(scrollUpOn, 0, 0);
        } else {
            g.drawImageAt(scrollUpOff, 0, 0);
        }
        if (firstDisplayedIcon + numVisibleButtons < buttonIcons.size()) {
            g.drawImageAt(scrollDownOn, 0, getBottom() - (buttonHeight / 2));
        } else {
            g.drawImageAt(scrollDownOff, 0, getBottom() - (buttonHeight / 2));
        }

        for (int i = 0; i < numVisibleButtons; ++i) {
            auto x = (i % cols) * buttonWidth;
            auto y = (i / cols) * buttonHeight + buttonHeight / 2;
            auto buttonIndex = i + firstDisplayedIcon;
            if (buttonIndex == selectionIndex) {
                g.drawImageAt(buttonDownBackground, x, y);
            } else if (buttonIndex < buttonIcons.size()) {
                g.drawImageAt(buttonUpBackground, x, y);
            } else {
                g.drawImageAt(buttonOffBackground, x, y);
                continue;
            }
            auto w = buttonIcons[buttonIndex].getWidth();
            auto h = buttonIcons[buttonIndex].getHeight();
            g.drawImageAt(buttonIcons[buttonIndex], x + buttonWidth / 2 - w / 2, y + buttonHeight / 2 - h / 2);
        }
    } else {
        for (int i = 0; i < numVisibleButtons; ++i) {
            auto x = (i % cols) * buttonWidth;
            auto y = (i / cols) * buttonHeight;
            auto buttonIndex = i + firstDisplayedIcon;
            if (buttonIndex == selectionIndex) {
                g.drawImageAt(buttonDownBackground, x, y);
            } else if (buttonIndex < buttonIcons.size()) {
                g.drawImageAt(buttonUpBackground, x, y);
            } else {
                g.drawImageAt(buttonOffBackground, x, y);
                continue;
            }
            auto w = buttonIcons[buttonIndex].getWidth();
            auto h = buttonIcons[buttonIndex].getHeight();
            g.drawImageAt(buttonIcons[buttonIndex], x + buttonWidth / 2 - w / 2, y + buttonHeight / 2 - h / 2);
        }

    }
}
void ButtonSelector::parameterValueChanged (int parameterIndex, float newValue)
{
    selectionIndex = parameterToAttachTo->getIndex();
}

void ButtonSelector::mouseDown (const juce::MouseEvent& event)
{
    if (!event.mouseWasClicked ()) {
        return;
    }
    if (numVisibleButtons < buttonIcons.size()) {
        if ((event.getPosition().getY() < (buttonHeight / 2)) && (firstDisplayedIcon >= 2)) {
            // scroll up button
            firstDisplayedIcon -= 2;
        } else if ((event.position.getY() > (getHeight() - buttonHeight / 2)) && (firstDisplayedIcon + numVisibleButtons < buttonIcons.size())) {
            firstDisplayedIcon += 2;
        } else {
            auto r = ((int)event.position.getY() - buttonHeight / 2) / buttonHeight;
            auto c = (int)event.position.getX() / buttonWidth;
            auto ind = r * cols + c + firstDisplayedIcon;
            if (ind < buttonIcons.size()) {
                selectionIndex = ind;
            }
        }
    } else {
        auto r = (int)event.position.getY() / buttonHeight;
        auto c = (int)event.position.getX() / buttonWidth;
        auto ind = r * cols + c;
        if (ind < buttonIcons.size()) {
            selectionIndex = ind;
        }
    }
    *parameterToAttachTo = selectionIndex;

    repaint();
}

void ButtonSelector::mouseWheelMove (const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel)
{
    if ((wheel.deltaY > 0) && (firstDisplayedIcon >= 2)) {
        firstDisplayedIcon -= 2;
    } else if ((wheel.deltaY < 0) && (firstDisplayedIcon + numVisibleButtons < buttonIcons.size())) {
        firstDisplayedIcon += 2;
    }
    repaint();
}