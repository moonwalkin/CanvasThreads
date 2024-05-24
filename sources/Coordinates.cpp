#include <QDebug>
#include <QRandomGenerator>
#include "../headers/Coordinates.h"

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
    QRandomGenerator *random = QRandomGenerator::global();
    unsigned short randomX = random->bounded(margin, canvasWidth - margin);
    unsigned short randomY = random->bounded(margin, canvasHeight - margin);
    qDebug() << "X:" << randomX << " Y: " << randomY;
    return Coordinates(randomX, randomY);
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
