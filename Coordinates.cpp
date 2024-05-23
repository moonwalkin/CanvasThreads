#include <QDebug>
#include "Coordinates.h"

Coordinates::Coordinates(unsigned short x, unsigned short y) {
    this->x = x;
    this->y = y;
}

Coordinates::Coordinates() {}

Coordinates::Coordinates(const Coordinates &other) {
    x = other.x;
    y = other.y;
}

Coordinates Coordinates::generate(unsigned short canvasWidth, unsigned short canvasHeight) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> x(margin, canvasWidth - margin);
    std::uniform_int_distribution<std::mt19937::result_type> y(margin, canvasHeight - margin);
    qDebug() << "X:" << x(rng) << " Y: " << y(rng);
    return Coordinates(x(rng), y(rng));
}

unsigned short Coordinates::getX() const {
    return x;
}

unsigned short Coordinates::getY() const {
    return y;
}

bool Coordinates::operator==(const Coordinates &other) const {
    return (abs(x - other.x) <= possibleDifference) && (abs(y - other.y) <= possibleDifference);
}

bool Coordinates::operator!=(const Coordinates &other) const {
    return !(*this == other);
}
