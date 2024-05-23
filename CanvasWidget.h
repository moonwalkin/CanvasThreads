#ifndef CANVAS_THREADS_CANVASWIDGET_H
#define CANVAS_THREADS_CANVASWIDGET_H

#include <QWidget>
#include <mutex>
#include "CoordinatesWithColor.h"
#include "MyPoint.h"

enum Action {
    AddNewColor,
    ChangeColorsBrightness
};

const unsigned int percent = 1;

const unsigned short pointWidth = 15;

class CanvasWidget : public QWidget {

public:
    CanvasWidget(QWidget *parent = nullptr) : QWidget(parent) {}

private:
    std::mutex mutex;
    QMap<MyPoint, QColor> coordinates = QMap<MyPoint, QColor>();

    void changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor);
    QColor blendColors(QColor oldColor, QColor currentColor);
    void changeBrightness();
    QColor createRandomColor(QColor oldColor, QColor currentColor);
public slots:
    void paintPixel(CoordinatesWithColor coordinatesWithColor, Action action);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif //CANVAS_THREADS_CANVASWIDGET_H
