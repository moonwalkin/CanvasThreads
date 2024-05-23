#ifndef CANVAS_THREADS_CANVASWIDGET_H
#define CANVAS_THREADS_CANVASWIDGET_H

#include <QWidget>
#include <mutex>
#include "CoordinatesWithColor.h"
#include "MyPoint.h"
#include <QPainter>
#include <QRandomGenerator>
#include <qdatetime.h>
#include "Message.h"
#include "QThread"


const unsigned int percent = 1;

const unsigned short pointWidth = 15;

class CanvasWidget : public QWidget {

public:
    CanvasWidget(QWidget *parent = nullptr) : QWidget(parent) {}
    void doWork(std::function<void(Message &message)> body);
    void stop();
    void removePixels();
private:
    QThread *blueThread;
    QThread *redThread;
    QThread *greenThread;
    std::mutex mutex;
    QMap<MyPoint, QColor> coordinates = QMap<MyPoint, QColor>();

    void changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor);
    QColor blendColors(QColor oldColor, QColor currentColor);
    void changeBrightness();
    QColor createRandomColor(QColor oldColor, QColor currentColor);
    void something(QColor color);
public slots:
    void paintPixel(CoordinatesWithColor *coordinatesWithColor);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif //CANVAS_THREADS_CANVASWIDGET_H
