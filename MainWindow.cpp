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

void MainWindow::threadPaint(CoordinatesWithColor coordinatesWithColor) {
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

    connect(&greenPixel, &PixelPainter::pixelPainted, this, &MainWindow::threadPaint);
    connect(&bluePixel, &PixelPainter::pixelPainted, this, &MainWindow::threadPaint);
    connect(&redPixel, &PixelPainter::pixelPainted, this, &MainWindow::threadPaint);

    greenPixel.start();
    bluePixel.start();
    redPixel.start();
    greenPixel.wait();
    bluePixel.wait();
    redPixel.wait();
}
