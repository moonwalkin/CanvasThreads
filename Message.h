#ifndef CANVAS_THREADS_MESSAGE_H
#define CANVAS_THREADS_MESSAGE_H

#include <chrono>
#include "Coordinates.h"
enum Color {
    Green,
    Blue,
    Red
};
class Message {
public:
    std::string threadName;
    Coordinates coordinates;
    Color pixelColor;
    std::chrono::time_point<std::chrono::steady_clock> timestamp;

    Message(std::string threadName, Coordinates coordinates, Color pixelColor,
            std::chrono::time_point<std::chrono::steady_clock> timestamp);
};


#endif //CANVAS_THREADS_MESSAGE_H
