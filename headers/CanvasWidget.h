#ifndef CANVAS_THREADS_CANVASWIDGET_H
#define CANVAS_THREADS_CANVASWIDGET_H

#include <QWidget>
#include <mutex>
#include "CoordinatesWithColor.h"
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
    void createThreads(std::function<void(Message &message)> body);
    void stop();
    void removePixels();
private:
    QThread *blueThread = nullptr;
    QThread *redThread = nullptr;
    QThread *greenThread = nullptr;
    std::mutex mutex;
    QMap<Coordinates, QColor> coordinates = QMap<Coordinates, QColor>();

    void changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor);
    QColor blendColors(QColor oldColor, QColor currentColor);
    void changeBrightness();
    QColor createRandomColor(QColor oldColor, QColor currentColor);
    void doWork(QColor color, QThread &thread, std::function<void(Message &message)> body);
    void setThreadsName();
    void startThreads();
public slots:
    void paintPixel(CoordinatesWithColor *coordinatesWithColor);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif //CANVAS_THREADS_CANVASWIDGET_H
