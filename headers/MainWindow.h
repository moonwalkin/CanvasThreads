#ifndef CANVAS_THREADS_MAINWINDOW_H
#define CANVAS_THREADS_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPainter>
#include <queue>
#include "ConsoleMessage.h"
#include "CanvasWidget.h"
#include "QReadWriteLock"
#include "QTimer"
#include "QMenu"
#include <QKeyEvent>
#include <QDialog>
#include "QLineEdit"
#include <QRadioButton>

const unsigned short canvasHeight = 820;
const unsigned short consoleHeight = 200;
const unsigned short clearConsoleDelay = 30000;
const unsigned short showMsgsDelay = 100;
const unsigned short dialogWidth = 300;
const unsigned short dialogHeight = 100;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    CanvasWidget *canvas{};
    QLineEdit *lineEdit{};
    QLabel *canvasLabel{};
    QTextEdit *console{};
    QReadWriteLock rwLock{};
    std::queue<ConsoleMessage> messageQueue{};
    QTimer *clearTimer{};
    QTimer *showMessagesTimer{};
    QDialog *dialog{};
    QRadioButton *setMillisButton{};
    QRadioButton *setMicrosButton{};

    void setupUi();

    void writeToQueue(ConsoleMessage &message);

    void stopTimers();

    void startTimers();

    void createTimers();

    void setupActions(QMenu &menu) const;

    void setupDialog();

private slots:

    void clearConsole();

    void showMessages();

    void showContextMenu(const QPoint &pos);

    void startPainting();

    void stopPainting();

    void keyPressEvent(QKeyEvent *event) override;

    void deletePixels();

    void changeDelay();
};

#endif //CANVAS_THREADS_MAINWINDOW_H
