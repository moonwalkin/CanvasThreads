#include "../headers/CoordinatesWithColor.h"

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

bool CoordinatesWithColor::operator==(const Coordinates &other) const {
    return coordinates == other;
}

bool CoordinatesWithColor::operator!=(const CoordinatesWithColor &other) const {
    return !(*this == other.coordinates);
}