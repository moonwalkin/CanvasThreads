#ifndef CANVAS_THREADS_COORDINATES_H
#define CANVAS_THREADS_COORDINATES_H

#include <random>

const unsigned short margin = 25;

class Coordinates {

public:
    unsigned short x;
    unsigned short y;
    Coordinates(unsigned short x, unsigned short y);
    Coordinates();

    static Coordinates generate(unsigned short canvasWidth, unsigned short canvasHeight);
};

#endif //CANVAS_THREADS_COORDINATES_H
