#include <QPainter>
#include "CanvasWidget.h"

void CanvasWidget::paintEvent(QPaintEvent *event) {
    if (coordinates.empty()) return;

    QPainter painter(this);

    for (CoordinatesWithColor coordinatesWithColor: coordinates) {
        painter.setPen(QPen(coordinatesWithColor.getColor(), pointWidth, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(coordinatesWithColor.getCoordinates().getX(), coordinatesWithColor.getCoordinates().getY());
    }
}

void CanvasWidget::paintPixel(CoordinatesWithColor coordinatesWithColor) {
    this->coordinates.push_back(coordinatesWithColor);
    update();
}