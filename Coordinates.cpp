#include "Coordinates.h"

Coordinates::Coordinates(unsigned short x, unsigned short y) {
    this->x = x;
    this->y = y;
}
Coordinates::Coordinates() {}

Coordinates Coordinates::generate(unsigned short canvasWidth, unsigned short canvasHeight){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> x(margin, canvasWidth - margin);
    std::uniform_int_distribution<std::mt19937::result_type> y(margin, canvasHeight - margin);
    return Coordinates(x(rng), y(rng));
}

unsigned short Coordinates::getX() {
    return x;
}

unsigned short Coordinates::getY() {
    return y;
}
