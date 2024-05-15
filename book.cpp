#include "Book.h"

// Constructor implementation
Book::Book(int id, const QString& name, const QString& author, const QString& publisher,
           int year, int pages, double price, const QString& cover)
    : id(id), name(name), author(author), publisher(publisher),
    year(year), pages(pages), price(price), cover(cover) {}

// Getters implementations
int Book::getId() const { return id; }
QString Book::getName() const { return name; }
QString Book::getAuthor() const { return author; }
QString Book::getPublisher() const { return publisher; }
int Book::getYear() const { return year; }
int Book::getPages() const { return pages; }
double Book::getPrice() const { return price; }
QString Book::getCover() const { return cover; }
