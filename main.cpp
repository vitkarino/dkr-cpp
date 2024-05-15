#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    // Ініціалізація додатка
    QApplication app(argc, argv);

    // Створення головного вікна
    MainWindow mainWindow;
    mainWindow.setWindowTitle("ДКР");
    mainWindow.show();

    // Запуск головного циклу обробки подій
    return app.exec();
}
