#include "MyPoint.h"


bool MyPoint::operator==(const MyPoint &other) const {
    return isCloseEnough(x(), other.x()) && isCloseEnough(y(), other.y());
}

bool MyPoint::operator!=(const MyPoint &other) const {
    return !(*this == other);
}

bool MyPoint::operator<(const MyPoint &other) const {
    if (y() == other.y()) {
        return isCloseEnough(x(), other.x());
    }
    return y() < other.y();
}

bool MyPoint::operator>(const MyPoint &other) const {
    if (y() == other.y()) {
        return isCloseEnough(x(), other.x());
    }
    return y() > other.y();
}

bool MyPoint::isCloseEnough(int a, int b) const {
    return abs(a - b) <= possibleDiff;
}

MyPoint::MyPoint(const QPoint &point) : QPoint(point) {}

MyPoint::MyPoint(int x, int y) : QPoint(x, y) {}
