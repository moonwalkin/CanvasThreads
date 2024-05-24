#ifndef CANVAS_THREADS_COORDINATES_H
#define CANVAS_THREADS_COORDINATES_H

#include <random>
#include "QPoint"

const unsigned short margin = 25;
const unsigned short possibleDifference = 10;

class Coordinates : public QPoint {
private:
    unsigned short x;
    unsigned short y;
    bool isCloseEnough(int a, int b) const;
    Coordinates(unsigned short x, unsigned short y);
public:
    Coordinates();
    Coordinates(const Coordinates& other);
    unsigned short getX() const;
    unsigned short getY() const;
    static Coordinates generate(unsigned short canvasWidth, unsigned short canvasHeight);
    bool operator==(const Coordinates& other) const;
    bool operator!=(const Coordinates& other) const;
    bool operator<(const Coordinates &other) const;
    bool operator>(const Coordinates &other) const;
};

#endif //CANVAS_THREADS_COORDINATES_H
