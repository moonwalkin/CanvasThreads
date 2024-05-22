#include "CanvasSize.h"

unsigned short CanvasSize::getWidth() {
    return width;
}

unsigned short CanvasSize::getHeight() {
    return height;
}

CanvasSize::CanvasSize() {}

CanvasSize::CanvasSize(unsigned short width, unsigned short height) {
    this->width = width;
    this->height = height;
}
