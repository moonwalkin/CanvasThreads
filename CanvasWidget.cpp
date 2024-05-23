#include "CanvasWidget.h"

void CanvasWidget::paintEvent(QPaintEvent *event) {
    if (coordinates.empty()) return;

    QPainter painter(this);

    QMapIterator<MyPoint, QColor> iterator(coordinates);
    while (iterator.hasNext()) {
        iterator.next();
        const QPoint &coords = iterator.key();
        const QColor &color = iterator.value();

        painter.setPen(QPen(color, pointWidth, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(coords);
    }
}

void CanvasWidget::something(QColor color) {
    Coordinates coord = Coordinates::generate(width(), height());
    paintPixel(new CoordinatesWithColor(coord, color));
    QDateTime currentTime = QDateTime::currentDateTime();
    Message message = Message(redThread->objectName().toStdString(), coord, color, currentTime);
    QThread::usleep(1000);
}

void CanvasWidget::doWork(std::function<void(Message &message)> body) {
    blueThread = QThread::create([this, body] {
        while (true) {
            if (blueThread->isInterruptionRequested()) return;
            Coordinates coordinates = Coordinates::generate(width(), height());
            paintPixel(new CoordinatesWithColor(coordinates, Qt::blue));
            QDateTime currentTime = QDateTime::currentDateTime();
            Message message = Message(blueThread->objectName().toStdString(), coordinates, Qt::blue, currentTime);
            QThread::usleep(1000);
            body(message);
        }
    });

    redThread = QThread::create([this, body] {
        while (true) {
            if (redThread->isInterruptionRequested()) return;
            Coordinates coordinates = Coordinates::generate(width(), height());
            paintPixel(new CoordinatesWithColor(coordinates, Qt::red));
            QDateTime currentTime = QDateTime::currentDateTime();
            Message message = Message(redThread->objectName().toStdString(), coordinates, Qt::red, currentTime);
            QThread::usleep(1000);
            body(message);
        }
    });


    greenThread = QThread::create([this, body] {
        while (true) {
            if (greenThread->isInterruptionRequested()) return;
            Coordinates coordinates = Coordinates::generate(width(), height());
            paintPixel(new CoordinatesWithColor(coordinates, Qt::green));
            QDateTime currentTime = QDateTime::currentDateTime();
            Message message = Message(greenThread->objectName().toStdString(), coordinates, Qt::green, currentTime);
            QThread::usleep(1000);
            body(message);
        }
    });

    blueThread->setObjectName(QString("Blue Thread"));
    greenThread->setObjectName(QString("Green Thread"));
    redThread->setObjectName(QString("Red Thread"));
    blueThread->start();
    greenThread->start();
    redThread->start();
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
    int x = coordinatesWithColor.getCoordinates().getX();
    int y = coordinatesWithColor.getCoordinates().getY();
    const QColor &currentColor = coordinatesWithColor.getColor();
    const MyPoint currentCoordinates = MyPoint(x, y);
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
    QMap<MyPoint, QColor>::iterator iterator = coordinates.begin();
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
    redThread->quit();
    greenThread->quit();
    blueThread->quit();
}

void CanvasWidget::removePixels() {
    coordinates.clear();
    update();
}


