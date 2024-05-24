#ifndef CANVAS_THREADS_MAINWINDOW_H
#define CANVAS_THREADS_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPainter>
#include <queue>
#include "Message.h"
#include "CanvasWidget.h"
#include "QReadWriteLock"
#include "QTimer"
#include "QMenu"
#include <QKeyEvent>

const unsigned short canvasHeight = 820;
const unsigned short consoleHeight = 200;
const unsigned short clearConsoleDelay = 30000;
const unsigned short showMsgsDelay = 100;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private:
    CanvasWidget *canvas{};
    QLabel *canvasLabel{};
    QTextEdit *console{};
    QReadWriteLock rwLock;
    std::queue<Message> messageQueue;
    QTimer *clearTimer;
    QTimer *showMessagesTimer;
    void setupUi();
    void writeToQueue(Message &message);
    void stopTimers();
    void startTimers();
    void createTimers();
    void setupActions(QMenu &menu) const;
private slots:
    void clearConsole();
    void showMessages();
    void showContextMenu(const QPoint &pos);
    void startPainting();
    void stopPainting();
    void keyPressEvent(QKeyEvent *event) override;
    void deletePixels();
};

#endif //CANVAS_THREADS_MAINWINDOW_H
