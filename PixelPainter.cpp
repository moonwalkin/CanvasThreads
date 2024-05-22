#include <QPixmap>
#include "PixelPainter.h"

void PixelPainter::run() {
    QColor pixelColor;
    if (threadName == "Green")
        pixelColor = Qt::green;
    else if (threadName == "Blue")
        pixelColor = Qt::blue;
    else if (threadName == "Red")
        pixelColor = Qt::red;

    Coordinates coordinates = Coordinates::generate(canvasSize.getWidth(), canvasSize.getHeight());

    emit pixelPainted(CoordinatesWithColor(coordinates, pixelColor));
}

PixelPainter::PixelPainter(QString threadName, CanvasSize canvasSize) {
    this->threadName = threadName;
    this->canvasSize = canvasSize;
}

PixelPainter::PixelPainter() {}
