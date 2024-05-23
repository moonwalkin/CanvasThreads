#include <iomanip>
#include "MainWindow.h"

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    canvas = new CanvasWidget();
    canvasLabel = new QLabel();
    console = new QTextEdit();
    QPalette palette = console->palette();
    console->setFixedHeight(consoleHeight);
    console->setFont(QFont("Arial", 12));
    palette.setColor(QPalette::Base, Qt::black);
    palette.setColor(QPalette::Text, Qt::white);
    console->setPalette(palette);
    layout->addWidget(canvas);
    layout->addWidget(canvasLabel);
    layout->addWidget(console);
    canvas->setFixedHeight(canvasHeight);
    canvas->setStyleSheet("border: 1px solid purple;");
    setCentralWidget(centralWidget);
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUi();
    setupConnections();
}

void MainWindow::setupConnections() {
    CanvasSize canvasSize = CanvasSize(canvas->width(), canvas->height());
    createPixelTreads(canvasSize);
}

void MainWindow::paint(CoordinatesWithColor coordinatesWithColor, Action action) {
//    canvas->paintPixel(coordinatesWithColor, action);
}

void MainWindow::writeToQueue(Message &message) {
    rwLock.lockForWrite();
    messageQueue.push(message);
    rwLock.unlock();
}

void MainWindow::createPixelTreads(CanvasSize canvasSize) {
    createTimer(SLOT(clearConsole()), 30000);
    createTimer(SLOT(showMessages()), 100);

    QThread *thread = QThread::create([this] {
        while (1) {
            Coordinates coordinates = Coordinates::generate(1920, 800);
            canvas->paintPixel(CoordinatesWithColor(coordinates, Qt::blue), AddNewColor);
            QDateTime currentTime = QDateTime::currentDateTime();
            Message message = Message("blueThread", coordinates, Qt::blue, currentTime);
            writeToQueue(message);
            QThread::msleep(1000);
        }
    });
    QThread *thread2 = QThread::create([this] {
        while (1) {
            Coordinates coordinates = Coordinates::generate(1920, 800);
            canvas->paintPixel(CoordinatesWithColor(coordinates, Qt::red), AddNewColor);
            QDateTime currentTime = QDateTime::currentDateTime();
            Message message = Message("redThread", coordinates, Qt::red, currentTime);
            writeToQueue(message);
            QThread::usleep(1000);
        }
    });
    QThread *thread3 = QThread::create([this] {
        while (1) {
            Coordinates coordinates = Coordinates::generate(1920, 800);
            canvas->paintPixel(CoordinatesWithColor(coordinates, Qt::green), AddNewColor);
            QDateTime currentTime = QDateTime::currentDateTime();
            Message message = Message("greenThread", coordinates, Qt::green, currentTime);
            writeToQueue(message);
            QThread::msleep(1000);
        }
    });
    QThread *thread4 = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::green),
                               ChangeColorsBrightness);
            QThread::msleep(1000);
        }
    });

//    QThread *thread5 = QThread::create([this] {
//        while (1) {
//
//        }
//    });
    thread->start();
//    thread2->start();
//    thread3->start();
//    thread4->start();
//    thread5->start();
}

void MainWindow::showMessages() {
    while (!messageQueue.empty()) {
        Message message = messageQueue.front();
        qDebug() << "showed";
        console->append(message.toString());
        messageQueue.pop();
    }
}

void MainWindow::clearConsole() {
    qDebug() << "called";
    console->clear();
}

void MainWindow::createTimer(const char* slot, int delay) {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, slot);
    timer->start(delay);
}
