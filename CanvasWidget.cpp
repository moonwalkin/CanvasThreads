#include <QPainter>
#include "CanvasWidget.h"
#include "algorithm"

void CanvasWidget::paintEvent(QPaintEvent *event) {
    if (coordinates.empty()) return;

    QPainter painter(this);

    for (CoordinatesWithColor coordinatesWithColor: coordinates) {
        painter.setPen(QPen(coordinatesWithColor.getColor(), pointWidth, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(coordinatesWithColor.getCoordinates().getX(), coordinatesWithColor.getCoordinates().getY());
    }
}

void CanvasWidget::paintPixel(CoordinatesWithColor coordinatesWithColor) {
    mutex.lock();
    changeColorIfCoordinatesExists(coordinatesWithColor);
    mutex.unlock();
    update();
}

void CanvasWidget::changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor) {
    auto it = std::find(coordinates.begin(), coordinates.end(), coordinatesWithColor.getCoordinates());
    if (it == coordinates.end()) {
        coordinates.push_back(coordinatesWithColor);
    } else {
        //        std::vector<QColor> colors = std::vector<QColor>();
//        colors.push_back(coordinatesWithColor.getColor());
//        colors.push_back(it.base()->getColor());
        coordinates.push_back(CoordinatesWithColor(coordinatesWithColor.getCoordinates(), Qt::yellow));
    }
}
