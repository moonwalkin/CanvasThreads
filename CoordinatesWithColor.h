
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
};


#endif //CANVAS_THREADS_COORDINATESWITHCOLOR_H
