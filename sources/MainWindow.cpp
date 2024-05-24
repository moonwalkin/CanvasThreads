#include "../headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUi();
    createTimers();
    startPainting();
}

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
    canvas->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(canvas, &CanvasWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    setCentralWidget(centralWidget);
}

void MainWindow::showContextMenu(const QPoint &pos) {
    QMenu menu;
    setupActions(menu);
    menu.exec(mapToGlobal(pos));
}

void MainWindow::setupActions(QMenu &menu) const {
    QAction *startAction = menu.addAction("Start");
    QAction *stopAction = menu.addAction("Stop");
    QAction *deleteAction = menu.addAction("Delete");
    startAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    stopAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    deleteAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    connect(startAction, &QAction::triggered, this, &MainWindow::startPainting);
    connect(stopAction, &QAction::triggered, this, &MainWindow::stopPainting);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deletePixels);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_R) {
        deletePixels();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_P) {
        startPainting();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S) {
        stopPainting();
    }
}

void MainWindow::writeToQueue(Message &message) {
    rwLock.lockForWrite();
    messageQueue.push(message);
    rwLock.unlock();
}

void MainWindow::showMessages() {
    while (!messageQueue.empty()) {
        Message message = messageQueue.front();
        console->append(message.toString());
        messageQueue.pop();
    }
}

void MainWindow::clearConsole() {
    console->clear();
}

void MainWindow::createTimers() {
    clearTimer = new QTimer(this);
    showMessagesTimer = new QTimer(this);
    connect(clearTimer, SIGNAL(timeout()), this, SLOT(clearConsole()));
    connect(showMessagesTimer, SIGNAL(timeout()), this, SLOT(showMessages()));
    startTimers();
}

void MainWindow::startPainting() {
    canvas->createThreads([this](Message &message) {
        writeToQueue(message);
    });
    startTimers();
}

void MainWindow::stopPainting() {
    canvas->stop();
    stopTimers();
}

void MainWindow::deletePixels() {
    canvas->removePixels();
    console->clear();
}

void MainWindow::stopTimers() {
    clearTimer->stop();
    showMessagesTimer->stop();
}

void MainWindow::startTimers() {
    clearTimer->start(clearConsoleDelay);
    showMessagesTimer->start(showMsgsDelay);
}
