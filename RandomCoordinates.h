#ifndef CANVAS_THREADS_RANDOMCOORDINATES_H
#define CANVAS_THREADS_RANDOMCOORDINATES_H

#include <random>

class RandomCoordinates {
public:
    unsigned short x;
    unsigned short y;
    RandomCoordinates(unsigned short x, unsigned short y);
    static RandomCoordinates generate(unsigned short canvasWidth, unsigned short canvasHeight);
};

#endif //CANVAS_THREADS_RANDOMCOORDINATES_H
