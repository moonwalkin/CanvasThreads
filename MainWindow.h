#ifndef CANVAS_THREADS_MAINWINDOW_H
#define CANVAS_THREADS_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include "PixelPainter.h"
#include <queue>
#include "Message.h"
#include "CanvasWidget.h"
#include "QReadWriteLock"

const unsigned short canvasHeight = 820;
const unsigned short consoleHeight = 200;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private:
    CanvasWidget *canvas{};
    QLabel *canvasLabel{};
    QTextEdit *console{};
    void setupConnections();
    void setupUi();
    void createPixelTreads(CanvasSize canvasSize);
    std::queue<Message> messageQueue;
    QReadWriteLock rwLock;
    void writeToQueue(Message &message);
    void createTimer(const char* slot, int delay);
private slots:
    void paint(CoordinatesWithColor coordinatesWithColor, Action action);
    void clearConsole();
    void showMessages();
};

#endif //CANVAS_THREADS_MAINWINDOW_H
