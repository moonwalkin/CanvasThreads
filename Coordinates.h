#ifndef CANVAS_THREADS_COORDINATES_H
#define CANVAS_THREADS_COORDINATES_H

#include <random>

const unsigned short margin = 25;

class Coordinates {
private:
    unsigned short x;
    unsigned short y;
    Coordinates(unsigned short x, unsigned short y);
public:
    Coordinates();
    unsigned short getX();
    unsigned short getY();
    static Coordinates generate(unsigned short canvasWidth, unsigned short canvasHeight);
};

#endif //CANVAS_THREADS_COORDINATES_H
