#include "CoordinatesWithColor.h"

CoordinatesWithColor::CoordinatesWithColor(Coordinates coordinates, QColor color) {
    this->coordinates = coordinates;
    this->color = color;
}

QColor CoordinatesWithColor::getColor() {
    return color;
}

Coordinates CoordinatesWithColor::getCoordinates() {
    return coordinates;
}
