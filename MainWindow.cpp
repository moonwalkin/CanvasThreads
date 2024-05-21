#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPainter>
#include <QGuiApplication>
#include <random>
#include "MainWindow.h"

void MainWindow::setupUi() {
    QPixmap *canvas = new QPixmap(1920, 880);
    canvas->fill(Qt::white);
    QWidget * centralWidget = new QWidget();
    QVBoxLayout * layout = new QVBoxLayout(centralWidget);
    QLabel *canvasLabel = new QLabel();
    canvasLabel->setPixmap(*canvas);
    QTextEdit * console = new QTextEdit();
    console->setFixedHeight(200);
    console->setFont(QFont("Arial", 12));
    QPalette palette = console->palette();
    palette.setColor(QPalette::Base, Qt::black);
    palette.setColor(QPalette::Text, Qt::white);
    console->setPalette(palette);
    layout->addWidget(canvasLabel);
    layout->addWidget(console);
    setCentralWidget(centralWidget);
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUi();
}