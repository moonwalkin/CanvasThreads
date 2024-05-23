
#ifndef CANVAS_THREADS_COORDINATESWITHCOLOR_H
#define CANVAS_THREADS_COORDINATESWITHCOLOR_H


#include <QColor>
#include "Coordinates.h"

class CoordinatesWithColor {
private:
    QColor color;
    Coordinates coordinates;
public:
    CoordinatesWithColor(Coordinates coordinates, QColor color);
    QColor getColor();
    Coordinates getCoordinates();
    void setColor(QColor newColor);
    bool operator==(const Coordinates& other) const;
    bool operator!=(const CoordinatesWithColor& other) const;
};


#endif //CANVAS_THREADS_COORDINATESWITHCOLOR_H
