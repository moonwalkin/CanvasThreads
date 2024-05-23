#ifndef CANVAS_THREADS_CANVASWIDGET_H
#define CANVAS_THREADS_CANVASWIDGET_H

#include <QWidget>
#include <mutex>
#include "CoordinatesWithColor.h"

enum Action {
    AddNewColor,
    ChangeColorsBrightness
};


const unsigned short pointWidth = 15;
class MyPoint : public QPoint {
public:
    MyPoint(int x = 0, int y = 0) : QPoint(x, y) {}
    MyPoint(const QPoint &point) : QPoint(point) {}

    bool operator==(const MyPoint &other) const {
        return isCloseEnough(x(), other.x()) && isCloseEnough(y(), other.y());
    }

    bool operator!=(const MyPoint &other) const {
        return !(*this == other);
    }

    bool operator<(const MyPoint &other) const {
        if (y() == other.y()) {
            return x() < other.x();
        }
        return y() < other.y();
    }

    bool operator>(const MyPoint &other) const {
        if (y() == other.y()) {
            return x() > other.x();
        }
        return y() > other.y();
    }

    bool isCloseEnough(int a, int b) const {
        return abs(a - b) <= possibleDifference;
    }
};
class CanvasWidget : public QWidget {

public:
    CanvasWidget(QWidget *parent = nullptr) : QWidget(parent) {}

private:
    std::mutex mutex;
    QMap<MyPoint, QColor> coordinates = QMap<MyPoint, QColor>();

    void changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor);
    QColor blendColors(QColor oldColor, QColor currentColor);
    void changeBrightness();
public slots:

    void paintPixel(CoordinatesWithColor coordinatesWithColor, Action action);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif //CANVAS_THREADS_CANVASWIDGET_H
