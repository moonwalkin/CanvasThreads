#ifndef CANVAS_THREADS_CONSOLEMESSAGE_H
#define CANVAS_THREADS_CONSOLEMESSAGE_H

#include <chrono>
#include "Coordinates.h"
#include <qstring.h>
#include <QColor>
#include <ctime>
#include <iomanip>
#include <qdatetime.h>

class ConsoleMessage {
public:
    std::string threadName;
    Coordinates coordinates;
    QColor pixelColor;
    QDateTime time;

    ConsoleMessage(std::string threadName, Coordinates &coordinates, QColor pixelColor,
                   QDateTime &time);

    QString toString() const;
private:
    std::string mapTimeToString() const;
};


#endif //CANVAS_THREADS_CONSOLEMESSAGE_H
