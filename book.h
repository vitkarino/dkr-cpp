#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book {
public:
    // Constructor to initialize the book with properties
    Book(int id, const QString& name, const QString& author, const QString& publisher,
         int year, int pages, double price, const QString& cover);

    // Getters for each property
    int getId() const;
    QString getName() const;
    QString getAuthor() const;
    QString getPublisher() const;
    int getYear() const;
    int getPages() const;
    double getPrice() const;
    QString getCover() const;

private:
    // Properties of the book
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
