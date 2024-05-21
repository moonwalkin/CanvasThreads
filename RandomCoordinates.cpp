#include "RandomCoordinates.h"

RandomCoordinates::RandomCoordinates(unsigned short x, unsigned short y) {
    this->x = x;
    this->y = y;
}

RandomCoordinates RandomCoordinates::generate(unsigned short canvasWidth, unsigned short canvasHeight){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> x(0, canvasWidth - 100);
    std::uniform_int_distribution<std::mt19937::result_type> y(0, canvasHeight - 100);
    return RandomCoordinates(x(rng), y(rng));
}