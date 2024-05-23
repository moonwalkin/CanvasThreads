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
        QColor currentColor = coordinatesWithColor.getColor();
        QColor oldColor = it.base()->getColor();
        QColor newColor = blendColors(oldColor, currentColor);
        coordinates.push_back(CoordinatesWithColor(coordinatesWithColor.getCoordinates(), newColor));
//        coordinates.push_back(CoordinatesWithColor(coordinatesWithColor.getCoordinates(), Qt::yellow));
    }
}

QColor CanvasWidget::blendColors(QColor oldColor, QColor currentColor) {
    if (oldColor == Qt::red && currentColor == Qt::green || oldColor == Qt::green && currentColor == Qt::red) {
        return QColor(Qt::yellow);
    } else if (oldColor == Qt::red && currentColor == Qt::blue || oldColor == Qt::blue && currentColor == Qt::red) {
        return QColor(Qt::magenta);
    } else if (oldColor == Qt::green && currentColor == Qt::blue || oldColor == Qt::blue && currentColor == Qt::green) {
        return QColor(Qt::cyan);
    }
    return Qt::gray;
}
