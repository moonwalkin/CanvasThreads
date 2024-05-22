#include "MainWindow.h"

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget();
    CanvasWidget *canvas = new CanvasWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QLabel *canvasLabel = new QLabel();
    QTextEdit *console = new QTextEdit();
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
}