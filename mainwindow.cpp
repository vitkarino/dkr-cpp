#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sortdialog.h"
#include "book.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTreeWidget>
#include <QDateTime>
#include <QSqlQuery>

// Конструктор головного вікна програми
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , logFile("log.txt")
    , currentId(1)
{
    ui->setupUi(this);

    // Відкриття файлу логів для запису
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

    initializeDatabase(); // Ініціалізація БЗ
    loadBooksFromDatabase(); // Завантаження книг з БЗ
}

// Деструктор головного вікна програми
MainWindow::~MainWindow()
{
    // Закриття файлу логів, якщо він відкритий
    if (logFile.isOpen()) {
        logFile.close();
    }
    delete ui; // Очищення інтерфейсу користувача
}

// Ініціалізація бази даних
void MainWindow::initializeDatabase() {
    // Створення БЗ
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("books.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Помилка бази даних", "Не вдалося відкрити базу даних.");
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS books ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "author TEXT, "
               "publisher TEXT, "
               "year INTEGER, "
               "pages INTEGER, "
               "price REAL, "
               "cover TEXT)");

    model = new QSqlTableModel(this, db);
    model->setTable("books");
    model->select();
}

// Завантаження книг з бази даних
void MainWindow::loadBooksFromDatabase() {
    QSqlQuery query("SELECT id, name, author, publisher, year, pages, price, cover FROM books");
    int maxId = 0;
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString author = query.value(2).toString();
        QString publisher = query.value(3).toString();
        int year = query.value(4).toInt();
        int pages = query.value(5).toInt();
        double price = query.value(6).toDouble();
        QString cover = query.value(7).toString();

        addBookToList(id, name, author, publisher, year, pages, price, cover);

        if (id > maxId) {
            maxId = id;
        }
    }
    currentId = maxId + 1;
}

// Видалення книги з бази даних
void MainWindow::removeBookFromDatabase(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM books WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        QMessageBox::warning(this, "Помилка бази даних", "Не вдалося видалити книгу з бази даних.");
    }
}

// Додавання книги до списку книг
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

// Слот для додавання нової книги через діалогове вікно
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

    int id = currentId++;

    QSqlQuery query;
    query.prepare("INSERT INTO books (id, name, author, publisher, year, pages, price, cover) "
                  "VALUES (:id, :name, :author, :publisher, :year, :pages, :price, :cover)");
    query.bindValue(":id", id);
    query.bindValue(":name", title);
    query.bindValue(":author", author);
    query.bindValue(":publisher", publisher);
    query.bindValue(":year", year);
    query.bindValue(":pages", pages);
    query.bindValue(":price", price);
    query.bindValue(":cover", cover);
    if (!query.exec()) {
        QMessageBox::warning(this, "Помилка бази даних", "Не вдалося зберегти книгу в базу даних.");
        return;
    }

    addBookToList(id, title, author, publisher, year, pages, price, cover);
}

// Слот для видалення обраної книги зі списку
void MainWindow::removeBook() {
    QTreeWidgetItem *item = ui->bookList->currentItem();
    if (item) {
        int id = item->text(0).toInt();
        QString title = item->text(1);
        removeBookFromDatabase(id);
        delete item;
        logMessage(QString("Видалена книга: %1").arg(title));
    } else {
        QMessageBox::warning(this, tr("Видалення книги"), tr("Будь ласка оберіть книгу для видалення."));
    }
}

// Слот для пошуку книг за назвою
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

// Слот для відкриття діалогового вікна сортування
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

// Слот для відкриття вікна "Про автора"
void MainWindow::aboutWindow() {
    QMessageBox::information(this, "Про автора", "Автор: Студент групи РЕ-21 - Кисіль Віктор Андрійович");
    logMessage("Відкрите вікно 'Про автора'");
}

// Метод для застосування сортування книг
void MainWindow::applySorting(const QString &author, const QString &publisher, const QString &yearStr) {
    int year = yearStr.toInt();

    for (int i = 0; i < ui->bookList->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->bookList->topLevelItem(i);
        bool match = true;

        if (!author.isEmpty() && item->text(2) != author) {
            match = false;
        }

        if (!publisher.isEmpty() && item->text(3) != publisher) {
            match = false;
        }

        if (!yearStr.isEmpty() && item->text(4).toInt() <= year) {
            match = false;
        }

        item->setHidden(!match);
    }

    logMessage(QString("Застосоване сортування: автор - %1, видавництво - %2, після року - %3").arg(author, publisher, yearStr));
}

// Метод для логування повідомлень
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
