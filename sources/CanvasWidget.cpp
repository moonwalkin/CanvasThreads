#include "../headers/CanvasWidget.h"

void CanvasWidget::paintEvent(QPaintEvent *event) {
    if (coordinates.empty()) return;

    QPainter painter(this);

    QMapIterator<Coordinates, QColor> iterator(coordinates);
    while (iterator.hasNext()) {
        iterator.next();
        const Coordinates &coords = iterator.key();
        const QColor &color = iterator.value();

        painter.setPen(QPen(color, pointWidth, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(coords);
    }
}

void CanvasWidget::doWork(QColor color, QThread &thread, std::function<void(ConsoleMessage &message)> body) {
    while (true) {
        if (thread.isInterruptionRequested()) return;
        Coordinates coord = Coordinates::generate(width(), height());
        paintPixel(new CoordinatesWithColor(coord, color));
        QDateTime currentTime = QDateTime::currentDateTime();
        ConsoleMessage message = ConsoleMessage(thread.objectName().toStdString(), coord, color, currentTime);
        body(message);
        if (measurementUnit == Millis)
            QThread::msleep(delay);
        else
            QThread::usleep(delay);
    }
}

void CanvasWidget::createThreads(std::function<void(ConsoleMessage &message)> body) {
    if (isThreadsRunning) return;

    blueThread = QThread::create([this, body] {
        doWork(Qt::blue, *blueThread, [body](ConsoleMessage &message) {
            body(message);
        });
    });
    redThread = QThread::create([this, body] {
        doWork(Qt::red, *redThread, [body](ConsoleMessage &message) {
            body(message);
        });
    });
    greenThread = QThread::create([this, body] {
        doWork(Qt::green, *greenThread, [body](ConsoleMessage &message) {
            body(message);
        });
    });

    brightnessThread = QThread::create([this, body] {
        while (true) {
            if (brightnessThread->isInterruptionRequested()) return;
            paintPixel(nullptr);
            if (measurementUnit == Millis)
                QThread::msleep(this->delay * 10);
            else
                QThread::usleep(this->delay * 10);
        }
    });

    setThreadsName();
    startThreads();
}

void CanvasWidget::startThreads() {
    blueThread->start();
    greenThread->start();
    redThread->start();
    brightnessThread->start();
    isThreadsRunning = true;
}

void CanvasWidget::paintPixel(CoordinatesWithColor *coordinatesWithColor) {
    mutex.lock();

    if (coordinatesWithColor == nullptr)
        changeBrightness();
    else
        changeColorIfCoordinatesExists(*coordinatesWithColor);

    update();
    mutex.unlock();
}

void CanvasWidget::changeColorIfCoordinatesExists(CoordinatesWithColor &coordinatesWithColor) {
    const QColor &currentColor = coordinatesWithColor.getColor();
    const Coordinates currentCoordinates = coordinatesWithColor.getCoordinates();
    if (coordinates.contains(currentCoordinates)) {
        QColor oldColor = coordinates.value(currentCoordinates);
        QColor newColor = blendColors(oldColor, currentColor);
        coordinates.insert(currentCoordinates, newColor);
    } else {
        coordinates.insert(currentCoordinates, currentColor);
    }
}

QColor CanvasWidget::blendColors(QColor oldColor, QColor currentColor) {
    if (oldColor == Qt::red && currentColor == Qt::green || oldColor == Qt::green && currentColor == Qt::red) {
        return Qt::yellow;
    } else if (oldColor == Qt::red && currentColor == Qt::blue || oldColor == Qt::blue && currentColor == Qt::red) {
        return Qt::magenta;
    } else if (oldColor == Qt::green && currentColor == Qt::blue || oldColor == Qt::blue && currentColor == Qt::green) {
        return Qt::cyan;
    }
    return createRandomColor(oldColor, currentColor);
}

void CanvasWidget::changeBrightness() {
    QMap<Coordinates, QColor>::iterator iterator = coordinates.begin();
    while (iterator != coordinates.end()) {
        QColor &color = iterator.value();

        int r = color.red();
        int g = color.green();
        int b = color.blue();

        double brightnessDelta = 255.0 * percent / 100.0;

        r = qBound(0, static_cast<int>(r + brightnessDelta), 255);
        g = qBound(0, static_cast<int>(g + brightnessDelta), 255);
        b = qBound(0, static_cast<int>(b + brightnessDelta), 255);

        color = QColor(r, g, b);
        ++iterator;
    }
}

QColor CanvasWidget::createRandomColor(QColor oldColor, QColor currentColor) {
    QRandomGenerator *random = QRandomGenerator::global();

    int randomRed = random->bounded(256);
    int randomGreen = random->bounded(256);
    int randomBlue = random->bounded(256);

    int newRed = (oldColor.red() + currentColor.red() + randomRed) % 256;
    int newGreen = (oldColor.green() + currentColor.green() + randomGreen) % 256;
    int newBlue = (oldColor.blue() + currentColor.blue() + randomBlue) % 256;

    return QColor::fromRgb(newRed, newGreen, newBlue);
}

void CanvasWidget::stop() {
    redThread->requestInterruption();
    greenThread->requestInterruption();
    blueThread->requestInterruption();
    brightnessThread->requestInterruption();
    redThread->quit();
    greenThread->quit();
    blueThread->quit();
    brightnessThread->quit();
    isThreadsRunning = false;
}

void CanvasWidget::removePixels() {
    coordinates.clear();
    update();
}

void CanvasWidget::setThreadsName() {
    blueThread->setObjectName(QString("Blue Thread"));
    greenThread->setObjectName(QString("Green Thread"));
    redThread->setObjectName(QString("Red Thread"));
    brightnessThread->setObjectName(QString("Brightness Thread"));
}

void CanvasWidget::changeDelayAndUnit(int newDelay, MeasurementUnit measurementUnit) {
    delay = newDelay;
    this->measurementUnit = measurementUnit;
}

CanvasWidget::~CanvasWidget() {
    stop();

    delete blueThread;
    delete redThread;
    delete greenThread;
    delete brightnessThread;
}