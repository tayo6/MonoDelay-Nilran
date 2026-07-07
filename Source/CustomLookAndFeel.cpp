#include "CustomLookAndFeel.h"

HadenianLookAndFeel::HadenianLookAndFeel()
{
    setColour (juce::Slider::textBoxTextColourId, HadenianColours::displayText);
    setColour (juce::Slider::textBoxBackgroundColourId, HadenianColours::displayBg);
    setColour (juce::Slider::textBoxOutlineColourId, HadenianColours::displayBorder);
    setColour (juce::Label::textColourId, HadenianColours::textDark);
    setColour (juce::ToggleButton::textColourId, HadenianColours::textDark);
}

void HadenianLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                             float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                                             juce::Slider&)
{
    auto bounds = juce::Rectangle<float> ((float) x, (float) y, (float) width, (float) height).reduced (4.0f);
    auto diameter = juce::jmin (bounds.getWidth(), bounds.getHeight());
    auto radius = diameter * 0.5f;
    auto centre = bounds.getCentre();
    auto rc = juce::Rectangle<float> (radius * 2.0f, radius * 2.0f).withCentre (centre);

    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Outer rim shadow
    g.setColour (HadenianColours::knobRim);
    g.fillEllipse (rc);

    // Knob body gradient
    auto bodyRect = rc.reduced (radius * 0.08f);
    juce::ColourGradient grad (HadenianColours::knobBodyLight, centre.x, bodyRect.getY(),
                                HadenianColours::knobBody, centre.x, bodyRect.getBottom(), false);
    g.setGradientFill (grad);
    g.fillEllipse (bodyRect);

    // Track arc (unfilled)
    juce::Path track;
    auto arcRadius = radius * 0.98f;
    track.addCentredArc (centre.x, centre.y, arcRadius, arcRadius, 0.0f,
                          rotaryStartAngle, rotaryEndAngle, true);
    g.setColour (HadenianColours::panelBorder);
    g.strokePath (track, juce::PathStrokeType (2.2f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    // Value arc (filled)
    juce::Path valueTrack;
    valueTrack.addCentredArc (centre.x, centre.y, arcRadius, arcRadius, 0.0f,
                               rotaryStartAngle, angle, true);
    g.setColour (HadenianColours::accentBlue);
    g.strokePath (valueTrack, juce::PathStrokeType (2.6f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    // Pointer line
    juce::Path pointer;
    auto pointerLength = radius * 0.62f;
    auto pointerThickness = juce::jmax (2.2f, radius * 0.11f);
    pointer.addRoundedRectangle (-pointerThickness * 0.5f, -pointerLength, pointerThickness, pointerLength * 0.9f, pointerThickness * 0.5f);
    g.setColour (HadenianColours::knobPointer);
    g.fillPath (pointer, juce::AffineTransform::rotation (angle).translated (centre));

    // Centre cap
    g.setColour (HadenianColours::knobRim);
    g.fillEllipse (juce::Rectangle<float> (radius * 0.22f, radius * 0.22f).withCentre (centre));
}

void HadenianLookAndFeel::drawToggleButton (juce::Graphics& g, juce::ToggleButton& button,
                                             bool shouldDrawButtonAsHighlighted, bool)
{
    auto bounds = button.getLocalBounds().toFloat().reduced (1.0f);
    auto cornerSize = bounds.getHeight() * 0.28f;

    g.setColour (HadenianColours::displayBg.darker (shouldDrawButtonAsHighlighted ? 0.05f : 0.0f));
    g.fillRoundedRectangle (bounds, cornerSize);
    g.setColour (HadenianColours::displayBorder);
    g.drawRoundedRectangle (bounds, cornerSize, 1.4f);

    auto ledDiameter = bounds.getHeight() * 0.42f;
    auto ledBounds = juce::Rectangle<float> (ledDiameter, ledDiameter)
                        .withCentre ({ bounds.getY() + bounds.getHeight() * 0.5f + bounds.getX() + ledDiameter * 0.7f,
                                       bounds.getCentreY() });
    ledBounds.setX (bounds.getX() + bounds.getHeight() * 0.32f);

    g.setColour (button.getToggleState() ? HadenianColours::accentBlue : HadenianColours::accentBlueOff);
    g.fillEllipse (ledBounds);

    g.setColour (HadenianColours::textDark);
    g.setFont (juce::Font (bounds.getHeight() * 0.5f, juce::Font::bold));
    auto textArea = bounds.withTrimmedLeft (bounds.getHeight() * 0.9f);
    g.drawText (button.getButtonText(), textArea, juce::Justification::centredLeft);
}

juce::Font HadenianLookAndFeel::getLabelFont (juce::Label& label)
{
    return juce::Font (juce::jmax (11.0f, label.getHeight() * 0.7f));
}
