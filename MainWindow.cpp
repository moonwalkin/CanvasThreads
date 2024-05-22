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

void MainWindow::paint(CoordinatesWithColor coordinatesWithColor) {
    canvas->paintPixel(coordinatesWithColor);
}

void MainWindow::createPixelTreads(CanvasSize canvasSize) {
    std::vector<PixelPainter> threads = std::vector<PixelPainter>();
    PixelPainter greenPixel = PixelPainter("Green", canvasSize);
    PixelPainter bluePixel = PixelPainter("Blue", canvasSize);
    PixelPainter redPixel = PixelPainter("Red", canvasSize);

//    threads.push_back(greenPixel);
//    threads.push_back(bluePixel);
//    threads.push_back(bluePixel);

    connect(&greenPixel, &PixelPainter::pixelPainted, this, &MainWindow::paint);
    connect(&bluePixel, &PixelPainter::pixelPainted, this, &MainWindow::paint);
    connect(&redPixel, &PixelPainter::pixelPainted, this, &MainWindow::paint);

    QThread *thread = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::blue));
            QThread::msleep(200);
        }
    });
    QThread *thread2 = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::red));
            QThread::msleep(200);
        }
    });
    QThread *thread3 = QThread::create([this] {
        while (1) {
            canvas->paintPixel(CoordinatesWithColor(Coordinates::generate(1920, 800), Qt::green));
            QThread::msleep(200);
        }
    });
    thread->start();
    thread2->start();
    thread3->start();
//    greenPixel.start();
//    bluePixel.start();
//    redPixel.start();
//    greenPixel.quit();
//    greenPixel.wait();
//    bluePixel.wait();
//    redPixel.wait();
}
