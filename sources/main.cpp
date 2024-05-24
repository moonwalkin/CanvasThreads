#include <QApplication>
#include "../headers/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.showFullScreen();
    return QApplication::exec();
}