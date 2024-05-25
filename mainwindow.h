#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Головне вікно програми
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор для ініціалізації головного вікна
    MainWindow(QWidget *parent = nullptr);

    // Деструкток для очищення ресурсів
    ~MainWindow();

private slots:
    // Слоти для обробки дій користувача
    void addBook();
    void removeBook();
    void searchBooks();
    void sortWindow();
    void aboutWindow();
    void applySorting(const QString &author, const QString &publisher, const QString &yearStr);

private:
    // Приватні методи для внутрішнього використання
    void initializeBooks();
    void addBookToList(int id, const QString& title, const QString& author, const QString& publisher, int year, int pages, double price, const QString& cover);
    void logMessage(const QString &message);  // Метод для логування

    void initializeDatabase();
    void loadBooksFromDatabase();
    void saveBookToDatabase(const Book &book);
    void removeBookFromDatabase(int id);

    int currentId;

    QSqlDatabase db;
    QSqlTableModel *model;

    Ui::MainWindow *ui; // Вказівник на інтерфейс користувача
    QFile logFile;  // Файл для зберігання логів
};

#endif // MAINWINDOW_H
