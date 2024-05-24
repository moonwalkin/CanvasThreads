#ifndef CANVAS_THREADS_CANVASWIDGET_H
#define CANVAS_THREADS_CANVASWIDGET_H

#include <QWidget>
#include <mutex>
#include "CoordinatesWithColor.h"
#include <QPainter>
#include <QRandomGenerator>
#include <qdatetime.h>
#include "ConsoleMessage.h"
#include "QThread"


const unsigned int percent = 1;
const unsigned short pointWidth = 15;
const unsigned short defaultDelay = 1000;

enum MeasurementUnit {
    Millis,
    Micros
};

class CanvasWidget : public QWidget {

public:
    CanvasWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    ~CanvasWidget();

    void createThreads(std::function<void(ConsoleMessage &message)> body);

    void stop();

    void removePixels();

    void changeDelayAndUnit(int newDelay, MeasurementUnit measurementUnit);

private:
    QThread *blueThread = nullptr;
    QThread *redThread = nullptr;
    QThread *greenThread = nullptr;
    QThread *brightnessThread = nullptr;
    bool isThreadsRunning = false;
    int delay = defaultDelay;
    MeasurementUnit measurementUnit = Millis;
    std::mutex mutex;
    QMap<Coordinates, QColor> coordinates = QMap<Coordinates, QColor>();

    void changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor);

    void changeBrightness();

    void doWork(QColor color, QThread &thread, std::function<void(ConsoleMessage &message)> body);

    void setThreadsName();

    void startThreads();

    QColor blendColors(QColor oldColor, QColor currentColor);

    QColor createRandomColor(QColor oldColor, QColor currentColor);

public slots:

    void paintPixel(CoordinatesWithColor *coordinatesWithColor);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif //CANVAS_THREADS_CANVASWIDGET_H
