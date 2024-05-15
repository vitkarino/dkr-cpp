#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QDialogButtonBox>
#include <QAbstractButton>

namespace Ui {
class SortDialog;
}

// Діалогове вікно для сортування книг
class SortDialog: public QDialog {
    Q_OBJECT

public:
    // Конструктор для ініціалізації діалогового вікна сортування
    explicit SortDialog(const QStringList &authors, const QStringList &publishers, QWidget *parent = nullptr);

    // Деструктор для очищення ресурсів
    ~SortDialog();

    // Геттери для отримання вибраних значень
    QString getAuthor() const;
    QString getPublisher() const;
    QString getYear() const;

private slots:
    // Слот для обробки натискання кнопок у діалоговому вікні
    void handleButtonClicked(QAbstractButton *button);

private:
    Ui::SortDialog *ui; // Вказівник на інтерфейс користувача
};

#endif // SORTDIALOG_H
