#ifndef CANVAS_THREADS_MYPOINT_H
#define CANVAS_THREADS_MYPOINT_H
#include <QPoint>

const unsigned short possibleDiff = 10;

class MyPoint : public QPoint {
public:
    MyPoint(int x = 0, int y = 0);

    MyPoint(const QPoint &point);

    bool operator==(const MyPoint &other) const;

    bool operator!=(const MyPoint &other) const;

    bool operator<(const MyPoint &other) const;

    bool operator>(const MyPoint &other) const;

private:
    bool isCloseEnough(int a, int b) const;
};

#endif //CANVAS_THREADS_MYPOINT_H
