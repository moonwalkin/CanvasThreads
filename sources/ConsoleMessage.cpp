#include "../headers/ConsoleMessage.h"
ConsoleMessage::ConsoleMessage(std::string threadName, Coordinates &coordinates, QColor pixelColor,
                               QDateTime &time) {
    this->threadName = threadName;
    this->coordinates = coordinates;
    this->pixelColor = pixelColor;
    this->time = time;
}

QString ConsoleMessage::toString() const {
    std::string color;
    if (pixelColor == Qt::red) color = "Red";
    else if (pixelColor == Qt::blue) color = "Blue";
    else if (pixelColor == Qt::green) color = "Green";

    return QString::fromStdString(
            "Thread name: " + threadName + "\nColor: " + color +
            "\nCoordinates: x = " + std::to_string(this->coordinates.getX()) + ", y = " +
            std::to_string(this->coordinates.getY()) + "\nTime: " + mapTimeToString()
    );
}

std::string ConsoleMessage::mapTimeToString() const {
    int hour = time.time().hour();
    int minute = time.time().minute();
    int second = time.time().second();

    std::string hourStr = std::to_string(hour);
    std::string minuteStr = std::to_string(minute);
    std::string secondStr = std::to_string(second);

    return hourStr + ":" + minuteStr + ":" + secondStr;
}

