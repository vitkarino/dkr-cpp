#ifndef BOOK_H
#define BOOK_H

#include <QString>

// Клас з атрибутами
class Book {
public:
    // Конструктор (ініціалізує всі атрибути книги)
    Book(int id, const QString& name, const QString& author, const QString& publisher,
         int year, int pages, double price, const QString& cover);

    // Геттери для доступу до атрибутів
    int getId() const;
    QString getName() const;
    QString getAuthor() const;
    QString getPublisher() const;
    int getYear() const;
    int getPages() const;
    double getPrice() const;
    QString getCover() const;

private:
    // Приватні члени, що зберігають інформацію про книгу
    int id;
    QString name;
    QString author;
    QString publisher;
    int year;
    int pages;
    double price;
    QString cover;
};

#endif // BOOK_H
