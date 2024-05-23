#include <QPainter>
#include "CanvasWidget.h"

void CanvasWidget::paintEvent(QPaintEvent *event) {
    if (coordinates.empty()) return;

    QPainter painter(this);

    QMapIterator<MyPoint, QColor> iterator(coordinates);
    while (iterator.hasNext()) {
        iterator.next();
        const QPoint &coords = iterator.key();
        const QColor &color = iterator.value();

        painter.setPen(QPen(color, pointWidth, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(coords);
    }
}

void CanvasWidget::paintPixel(CoordinatesWithColor coordinatesWithColor, Action action) {
    mutex.lock();

    if (action == AddNewColor)
        changeColorIfCoordinatesExists(coordinatesWithColor);
    else
        changeBrightness();

    update();
    mutex.unlock();
}

void CanvasWidget::changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor) {
    int x = coordinatesWithColor.getCoordinates().getX();
    int y = coordinatesWithColor.getCoordinates().getY();
    const QColor &currentColor = coordinatesWithColor.getColor();
    const MyPoint currentCoordinates = MyPoint(x, y);
    if (coordinates.contains(currentCoordinates)) {
        QColor oldColor = coordinates.value(currentCoordinates);
        QColor newColor = blendColors(oldColor, currentColor);
        coordinates.insert(currentCoordinates, newColor);
    } else {
        coordinates.insert(currentCoordinates, currentColor);
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
    QMapIterator<MyPoint, QColor> iterator(coordinates);
    while (iterator.hasNext()) {
        iterator.next();
        QPoint point = iterator.key();
        QColor &color = coordinates[point];

        int r = color.red();
        int g = color.green();
        int b = color.blue();

        double brightnessDelta = 255.0 * 5 / 100.0;

        r = qBound(0, static_cast<int>(r + brightnessDelta), 255);
        g = qBound(0, static_cast<int>(g + brightnessDelta), 255);
        b = qBound(0, static_cast<int>(b + brightnessDelta), 255);

        color = QColor(r, g, b);
    }
}
