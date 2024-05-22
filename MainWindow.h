#ifndef CANVAS_THREADS_MAINWINDOW_H
#define CANVAS_THREADS_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include "PixelPainter.h"
#include "Message.h"
#include "CanvasWidget.h"

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

private slots:
    void paint(CoordinatesWithColor coordinatesWithColor);
};

#endif //CANVAS_THREADS_MAINWINDOW_H
