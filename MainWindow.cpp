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

void MainWindow::createPixelTreads(CanvasSize canvasSize) {
    QThread *thread = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::blue), AddNewColor);
            QThread::usleep(1000);
        }
    });
    QThread *thread2 = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::red), AddNewColor);
            QThread::usleep(1000);
        }
    });
    QThread *thread3 = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::green), AddNewColor);
            QThread::usleep(1000);
        }
    });
    QThread *thread4 = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::green),
                               ChangeColorsBrightness);
            QThread::msleep(1000);
        }
    });
    thread->start();
    thread2->start();
    thread3->start();
    thread4->start();
}