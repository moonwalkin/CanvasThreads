#ifndef CANVAS_THREADS_CANVASWIDGET_H
#define CANVAS_THREADS_CANVASWIDGET_H

#include <QWidget>
#include "CoordinatesWithColor.h"

const unsigned short pointWidth = 15;

class CanvasWidget : public QWidget {

public:
    CanvasWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    std::vector<CoordinatesWithColor> coordinates = std::vector<CoordinatesWithColor>();

public slots:

    void paintPixel(CoordinatesWithColor coordinatesWithColor);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif //CANVAS_THREADS_CANVASWIDGET_H
