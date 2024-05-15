#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addBook();
    void removeBook();
    void searchBooks();
    void sortWindow();
    void aboutWindow();
    void applySorting(const QString &author, const QString &publisher, const QString &yearStr);

private:
    void initializeBooks();
    void addBookToList(int id, const QString& title, const QString& author, const QString& publisher, int year, int pages, double price, const QString& cover);
    void logMessage(const QString &message);  // Новий метод для логування

    Ui::MainWindow *ui;
    QFile logFile;  // Файл для зберігання логів
};

#endif // MAINWINDOW_H
