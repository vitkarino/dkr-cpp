#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include "Book.h"

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
    void on_action3_triggered();
    void on_action5_triggered();
    void on_pushbutton3_clicked();
    void addBook();
    void removeBook();
    void searchBooks();
    void on_sortButton_clicked();
    void applySorting(const QString &author, const QString &publisher, const QString &yearStr);

private:
    QListWidget *listWidget;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
