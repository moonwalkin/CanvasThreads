#include <QDebug>
#include <QRandomGenerator>
#include "../headers/Coordinates.h"

Coordinates::Coordinates(unsigned short x, unsigned short y) : QPoint(x, y) {
    this->x = x;
    this->y = y;
}

Coordinates::Coordinates() {}

Coordinates::Coordinates(const Coordinates &other) : QPoint(other) {
    x = other.x;
    y = other.y;
}

Coordinates Coordinates::generate(unsigned short canvasWidth, unsigned short canvasHeight) {
    QRandomGenerator *random = QRandomGenerator::global();
    unsigned short randomX = random->bounded(margin, canvasWidth - margin);
    unsigned short randomY = random->bounded(margin, canvasHeight - margin);
    return Coordinates(randomX, randomY);
}

unsigned short Coordinates::getX() const {
    return x;
}

unsigned short Coordinates::getY() const {
    return y;
}

bool Coordinates::operator==(const Coordinates &other) const {
    return isCloseEnough(x, other.x) && isCloseEnough(y, other.y);
}

bool Coordinates::operator!=(const Coordinates &other) const {
    return !(*this == other);
}

bool Coordinates::operator<(const Coordinates &other) const {
    if (y == other.y) {
        return isCloseEnough(x, other.x);
    }
    return y < other.y;
}

bool Coordinates::operator>(const Coordinates &other) const {
    if (y == other.y) {
        return isCloseEnough(x, other.x);
    }
    return y > other.y;
}

bool Coordinates::isCloseEnough(int a, int b) const {
    return abs(a - b) <= possibleDifference;
}
