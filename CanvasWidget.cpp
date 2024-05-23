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

void CanvasWidget::paintPixel(CoordinatesWithColor coordinatesWithColor, Action action) {
    mutex.lock();

    if (action == AddNewColor)
        changeColorIfCoordinatesExists(coordinatesWithColor);
    else
        changeBrightness();

    mutex.unlock();
    update();
}

void CanvasWidget::changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor) {
    Coordinates currentCoordinates = coordinatesWithColor.getCoordinates();
    QColor currentColor = coordinatesWithColor.getColor();
    auto iterator = std::find(coordinates.begin(), coordinates.end(), currentCoordinates);
    if (iterator == coordinates.end()) {
        coordinates.push_back(CoordinatesWithColor(currentCoordinates, currentColor));
    } else {
        QColor oldColor = iterator.base()->getColor();
        QColor newColor = blendColors(oldColor, currentColor);
        coordinates.push_back(CoordinatesWithColor(coordinatesWithColor.getCoordinates(), newColor));
    }
}

QColor CanvasWidget::blendColors(QColor oldColor, QColor currentColor) {
    if (oldColor == Qt::red && currentColor == Qt::green || oldColor == Qt::green && currentColor == Qt::red) {
        return Qt::yellow;
    } else if (oldColor == Qt::red && currentColor == Qt::blue || oldColor == Qt::blue && currentColor == Qt::red) {
        return Qt::magenta;
    } else if (oldColor == Qt::green && currentColor == Qt::blue || oldColor == Qt::blue && currentColor == Qt::green) {
        return Qt::cyan;
    }
    return Qt::gray;
}

void CanvasWidget::changeBrightness() {
    for (auto &item: coordinates) {
        int r = item.getColor().red();
        int g = item.getColor().green();
        int b = item.getColor().blue();

        double brightnessDelta = 255.0 * 5 / 100.0;

        r = qBound(0, static_cast<int>(r + brightnessDelta), 255);
        g = qBound(0, static_cast<int>(g + brightnessDelta), 255);
        b = qBound(0, static_cast<int>(b + brightnessDelta), 255);

        item.setColor(QColor(r, g, b));
    }
}
