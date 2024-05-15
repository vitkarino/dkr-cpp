#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sortdialog.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTreeWidget>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , logFile("log.txt")  // Ініціалізація файлу логів
{
    ui->setupUi(this);

    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Помилка відкриття файлу"), tr("Не вдалося відкрити файл логів."));
    }

    // Підключення сигналів до слотів
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addBook);
    connect(ui->addBookAction, &QAction::triggered, this, &MainWindow::addBook);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeBook);
    connect(ui->removeBookAction, &QAction::triggered, this, &MainWindow::removeBook);
    connect(ui->sortAction, &QAction::triggered, this, &MainWindow::sortWindow);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sortWindow);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchBooks);
    connect(ui->aboutMe, &QAction::triggered, this, &MainWindow::aboutWindow);

    // Ініціалізація книг
    initializeBooks();
}

MainWindow::~MainWindow()
{
    if (logFile.isOpen()) {
        logFile.close();  // Закриття файлу логів
    }
    delete ui;
}


void MainWindow::initializeBooks() {
    addBookToList(1, "To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott & Co.", 1960, 281, 10.99, "Hardcover");
    addBookToList(2, "1984", "George Orwell", "Secker & Warburg", 1949, 328, 12.99, "Hardcover");
    addBookToList(3, "Moby Dick", "Herman Melville", "Harper & Brothers", 1851, 635, 15.99, "Hardcover");
    addBookToList(4, "The Great Gatsby", "F. Scott Fitzgerald", "Charles Scribner's Sons", 1925, 180, 8.99, "Paperback");
    addBookToList(5, "War and Peace", "Leo Tolstoy", "The Russian Messenger", 1869, 1225, 20.99, "Hardcover");
}

void MainWindow::addBookToList(int id, const QString& title, const QString& author, const QString& publisher, int year, int pages, double price, const QString& cover) {
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->bookList);
    item->setText(0, QString::number(id));
    item->setText(1, title);
    item->setText(2, author);
    item->setText(3, publisher);
    item->setText(4, QString::number(year));
    item->setText(5, QString::number(pages));
    item->setText(6, QString::number(price));
    item->setText(7, cover);
    ui->bookList->addTopLevelItem(item);

    logMessage(QString("Додана книга: %1").arg(title));
}

void MainWindow::addBook() {
    bool ok;
    QString title = QInputDialog::getText(this, tr("Нова книга"), tr("Назва:"), QLineEdit::Normal, QString(), &ok);
    if (!ok || title.isEmpty()) return;

    QString author = QInputDialog::getText(this, tr("Нова книга"), tr("Автор:"), QLineEdit::Normal, QString(), &ok);
    if (!ok || author.isEmpty()) return;

    QString publisher = QInputDialog::getText(this, tr("Нова книга"), tr("Видавництво:"), QLineEdit::Normal, QString(), &ok);
    if (!ok || publisher.isEmpty()) return;

    int year = QInputDialog::getInt(this, tr("Нова книга"), tr("Рік:"), 1900, 1500, 2100, 1, &ok);
    if (!ok) return;

    int pages = QInputDialog::getInt(this, tr("Нова книга"), tr("Сторінки:"), 1, 1, 10000, 1, &ok);
    if (!ok) return;

    double price = QInputDialog::getDouble(this, tr("Нова книга"), tr("Ціна:"), 0.0, 0.0, 10000.0, 2, &ok);
    if (!ok) return;

    QString cover = QInputDialog::getText(this, tr("Нова книга"), tr("Тип палітурки:"), QLineEdit::Normal, QString(), &ok);
    if (!ok || cover.isEmpty()) return;

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->bookList);
    item->setText(0, QString::number(ui->bookList->topLevelItemCount()));
    item->setText(1, title);
    item->setText(2, author);
    item->setText(3, publisher);
    item->setText(4, QString::number(year));
    item->setText(5, QString::number(pages));
    item->setText(6, QString::number(price));
    item->setText(7, cover);
    ui->bookList->addTopLevelItem(item);

    logMessage(QString("Додана нова книга: %1").arg(title));
}

void MainWindow::removeBook() {
    QTreeWidgetItem *item = ui->bookList->currentItem();
    if (item) {
        QString title = item->text(1);  // Оголошення змінної title перед її використанням
        delete item;
        logMessage(QString("Видалена книга: %1").arg(title));
    } else {
        QMessageBox::warning(this, tr("Видалення книги"), tr("Будь ласка оберіть книгу для видалення."));
    }
}


void MainWindow::searchBooks() {
    QString searchText = ui->searchLine->text().trimmed();
    if (searchText.isEmpty()) {
        for (int i = 0; i < ui->bookList->topLevelItemCount(); ++i) {
            QTreeWidgetItem *item = ui->bookList->topLevelItem(i);
            item->setHidden(false);
        }
        logMessage("Скидання пошуку");
        return;
    }

    for (int i = 0; i < ui->bookList->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->bookList->topLevelItem(i);
        if (item->text(1).contains(searchText, Qt::CaseInsensitive)) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
    logMessage(QString("Пошук книг за назвою: %1").arg(searchText));
}

void MainWindow::sortWindow() {
    QStringList authors;
    QStringList publishers;

    for (int i = 0; i < ui->bookList->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->bookList->topLevelItem(i);
        QString author = item->text(2);
        QString publisher = item->text(3);

        if (!authors.contains(author)) {
            authors.append(author);
        }

        if (!publishers.contains(publisher)) {
            publishers.append(publisher);
        }
    }

    SortDialog dialog(authors, publishers, this);
    if (dialog.exec() == QDialog::Accepted) {
        QString author = dialog.getAuthor();
        QString publisher = dialog.getPublisher();
        QString yearStr = dialog.getYear();

        applySorting(author, publisher, yearStr);
    }
}

void MainWindow::aboutWindow() {
    QMessageBox::information(this, "Про автора", "Автор: Студент групи РЕ-21 - Кисіль Віктор Андрійович");
    logMessage("Відкрите вікно 'Про автора'");
}

void MainWindow::applySorting(const QString &author, const QString &publisher, const QString &yearStr) {
    int year = yearStr.toInt();

    for (int i = 0; i < ui->bookList->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->bookList->topLevelItem(i);
        bool match = true;

        if (!author.isEmpty() && item->text(2) != author)
            match = false;

        if (!publisher.isEmpty() && item->text(3) != publisher)
            match = false;

        if (!yearStr.isEmpty() && item->text(4).toInt() != year)
            match = false;

        item->setHidden(!match);
    }
    logMessage(QString("Застосоване сортування: автор - %1, видавництво - %2, рік - %3").arg(author, publisher, yearStr));
}

void MainWindow::logMessage(const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString logEntry = QString("[%1] %2").arg(timestamp, message);

    // Додавання повідомлення до графічної консолі
    ui->consoleBlock->addItem(logEntry);
    ui->consoleBlock->scrollToBottom();  // Автоматичне прокручування до кінця

    // Запис повідомлення у файл логів
    if (logFile.isOpen()) {
        QTextStream out(&logFile);
        out << logEntry << "\n";
    }
}

