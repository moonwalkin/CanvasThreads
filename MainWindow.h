#ifndef CANVAS_THREADS_MAINWINDOW_H
#define CANVAS_THREADS_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QGuiApplication>
#include <queue>
#include <QPainter>
#include <QPushButton>
#include <iostream>
#include "WorkerThread.cpp"
#include "Message.h"

const unsigned short pointWidth = 15;
const unsigned short canvasHeight = 820;
const unsigned short consoleHeight = 200;

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);

    void setupUi();

    class CanvasWidget : public QWidget {
    public:
        CanvasWidget(QWidget *parent = nullptr) : QWidget(parent) {}

        std::vector<Coordinates> coordinates = std::vector<Coordinates>();

        void addPoint(int x, int y) {
            coordinates.push_back(Coordinates(x, y));
            update();
        }

    protected:
        void paintEvent(QPaintEvent *event) override {
            if (coordinates.empty()) return;

            QPainter painter(this);

            for (Coordinates coordinate: coordinates) {
                painter.setPen(QPen(Qt::red, pointWidth, Qt::SolidLine, Qt::RoundCap));
                painter.drawPoint(coordinate.x, coordinate.y);
            }
        }
    };
};

#endif //CANVAS_THREADS_MAINWINDOW_H
