#ifndef COLORS_H
#define COLORS_H

#include <QColor>

class SpectrumColors
{
public:
    SpectrumColors();

    static QColor red;
    static QColor green;
    static QColor blue;
    static QColor purple;
    static QColor yellow;
    static QColor orange;
    static QColor gray;
    static QColor black;
    static QColor defaultActiveColor;

    static const int COLOR_NUM = 6;
    static const int BLUE = 0;
    static const int PURPLE = 1;
    static const int RED = 2;
    static const int YELLOW = 3;
    static const int ORANGE = 4;
    static const int GREEN = 5;
    static const int GRAY = 6;
    static const int DEFAULT = BLUE;

    static QColor getColorFromName(const QString &colorName);
    static QColor getColorId(int id);
    static int toEnum(const QColor &color);
};

#endif // COLORS_H
