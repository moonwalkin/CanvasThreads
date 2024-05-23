#include <QPixmap>
#include "PixelPainter.h"

void PixelPainter::painting() {
    QColor pixelColor;
    if (threadName == "Green")
        pixelColor = Qt::green;
    else if (threadName == "Blue")
        pixelColor = Qt::blue;
    else if (threadName == "Red")
        pixelColor = Qt::red;
    Coordinates coordinates = Coordinates::generate(canvasSize.getWidth(), canvasSize.getHeight());

//    emit pixelPainted(CoordinatesWithColor(coordinates, pixelColor));
}

void PixelPainter::run() {
    QTimer timer;
    connect(&timer, &QTimer::timeout, this, &PixelPainter::painting);
    timer.start(1000); // Start the timer with a 1-second interval

    exec();
}

PixelPainter::PixelPainter(QString threadName, CanvasSize canvasSize) {
    this->threadName = threadName;
    this->canvasSize = canvasSize;
}

PixelPainter::PixelPainter() {}
