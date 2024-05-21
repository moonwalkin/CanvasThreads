#ifndef CANVAS_THREADS_MAINWINDOW_H
#define CANVAS_THREADS_MAINWINDOW_H

#include <QMainWindow>

enum Color {
    Green,
    Blue,
    Red
};

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
    void setupUi();
};

#endif //CANVAS_THREADS_MAINWINDOW_H
