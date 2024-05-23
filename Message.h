#ifndef CANVAS_THREADS_MESSAGE_H
#define CANVAS_THREADS_MESSAGE_H

#include <chrono>
#include "Coordinates.h"
#include <qstring.h>
#include <QColor>
#include <ctime>
#include <iomanip>
#include <qdatetime.h>

class Message {
public:
    std::string threadName;
    Coordinates coordinates;
    QColor pixelColor;
    QDateTime time;

    Message(std::string threadName, Coordinates &coordinates, QColor pixelColor,
            QDateTime &time);

    QString toString() const;
private:
    std::string mapTimeToString() const;
};


#endif //CANVAS_THREADS_MESSAGE_H
