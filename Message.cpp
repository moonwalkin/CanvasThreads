#include "Message.h"

Message::Message(std::string threadName, Coordinates coordinates, Color pixelColor,
                 std::chrono::time_point<std::chrono::steady_clock> timestamp) {
    this->threadName = threadName;
    this->coordinates = coordinates;
    this->pixelColor = pixelColor;
    this->timestamp = timestamp;
}

