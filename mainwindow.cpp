#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sortdialog.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action, &QAction::triggered, this, &MainWindow::addBook);
    connect(ui->action_2, &QAction::triggered, this, &MainWindow::removeBook);
    connect(ui->action_3, &QAction::triggered, this, &MainWindow::on_action3_triggered);
    connect(ui->action_5, &QAction::triggered, this, &MainWindow::on_action5_triggered);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushbutton3_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addBook);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::removeBook);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::searchBooks);
}

MainWindow::~MainWindow()
{
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

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, QString::number(ui->treeWidget->topLevelItemCount())); // Assuming ID is a sequential number
    item->setText(1, title);
    item->setText(2, author);
    item->setText(3, publisher);
    item->setText(4, QString::number(year));
    item->setText(5, QString::number(pages));
    item->setText(6, QString::number(price));
    item->setText(7, cover);
    ui->treeWidget->addTopLevelItem(item);
}


void MainWindow::removeBook() {
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (item) {
        delete item;  // This removes and deletes the item
    } else {
        QMessageBox::warning(this, tr("Видалення книги"), tr("Будь ласка оберіть книгу для видалення."));
    }
}

void MainWindow::searchBooks() {
    QString searchText = ui->lineEdit->text().trimmed();  // Get text from QLineEdit
    if (searchText.isEmpty()) {
        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
            QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
            item->setHidden(false);  // Show all items if the search text is empty
        }
        return;
    }

    // Filter items based on the title
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        if (item->text(1).contains(searchText, Qt::CaseInsensitive)) {  // Assuming the title is in the second column
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}

void MainWindow::on_pushbutton3_clicked() {
    SortDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_action5_triggered() {
    QMessageBox::information(this, "Про автора", "Автор: Студент групи РЕ-21 - Кисіль Віктор Андрійович"); // Pop-up using QMessageBox
}

void MainWindow::on_action3_triggered() {
    SortDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_sortButton_clicked() {
    SortDialog *dialog = new SortDialog(this);

    if (dialog->exec() == QDialog::Accepted) {
        QString author = dialog->getAuthor();
        QString publisher = dialog->getPublisher();
        QString yearStr = dialog->getYear();

        applySorting(author, publisher, yearStr);
    }

    delete dialog;
}

void MainWindow::applySorting(const QString &author, const QString &publisher, const QString &yearStr) {
    QDate year;
    if (!yearStr.isEmpty()) {
        year = QDate::fromString(yearStr, "yyyy");  // Convert string to QDate
        if (!year.isValid()) {
            QMessageBox::warning(this, "Invalid Date", "The entered year is invalid. Please use format YYYY.");
            return;
        }
    }

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        bool match = true;

        if (!author.isEmpty() && item->text(2) != author)
            match = false;

        if (!publisher.isEmpty() && item->text(3) != publisher)
            match = false;

        if (!yearStr.isEmpty() && QDate::fromString(item->text(4), "yyyy") != year)
            match = false;

        item->setHidden(!match);
    }
}




