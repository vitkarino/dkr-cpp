#include <QApplication>
#include "MainWindow.h"  // Ваш клас головного вікна

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Створення і налаштування головного вікна
    MainWindow mainWindow;
    mainWindow.setWindowTitle("ДКР");
    mainWindow.show();  // Показуємо головне вікно

    // Запуск основного циклу подій
    return app.exec();
}
