#ifndef CANVAS_THREADS_PIXELPAINTER_H
#define CANVAS_THREADS_PIXELPAINTER_H

#include <QThread>
#include <thread>
#include "CoordinatesWithColor.h"
#include "PixelPainter.moc"
#include "QTimer"
#include "CanvasSize.h"

class PixelPainter : public QThread {
Q_OBJECT

public:
    void run() override;

    PixelPainter(QString threadName, CanvasSize canvasSize);

    PixelPainter();

private slots:

    void painting();

private:
    QString threadName;
    CanvasSize canvasSize;
signals:

    void pixelPainted(CoordinatesWithColor coordinatesWithColor);
};

#endif //CANVAS_THREADS_PIXELPAINTER_H
