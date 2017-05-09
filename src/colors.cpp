#include "../include/colors.h"


QColor SpectrumColors::red = QColor(238, 52, 55);
QColor SpectrumColors::green = QColor(108, 210, 77);
QColor SpectrumColors::blue = QColor(40, 123, 219);
QColor SpectrumColors::purple = QColor(158, 24, 166);
QColor SpectrumColors::pink = QColor(245, 105, 145);
QColor SpectrumColors::yellow = QColor(253, 231, 43);
QColor SpectrumColors::orange = QColor(250, 121, 33);
QColor SpectrumColors::gray = QColor(50, 50, 50);
QColor SpectrumColors::black = QColor(0, 0, 0);


QColor SpectrumColors::defaultActiveColor = SpectrumColors::blue;



QColor SpectrumColors::getColorFromName(const QString &colorName)
{
    if (colorName == "red") {
        return red;
    } else if (colorName == "green") {
        return green;
    } else if (colorName == "blue") {
        return blue;
    } else if (colorName == "yellow") {
        return yellow;
    } else if (colorName == "purple") {
        return purple;
    } else if (colorName == "orange") {
        return orange;
    } else if (colorName == "gray") {
        return gray;
    } else if (colorName == "pink") {
        return pink;
    } else if (colorName == "default") {
        return defaultActiveColor;
    } else
        return defaultActiveColor;
}
