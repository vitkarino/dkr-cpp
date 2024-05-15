#include "sortdialog.h"
#include "./ui_sortdialog.h"

// Конструктор діалогового вікна сортування
SortDialog::SortDialog(const QStringList &authors, const QStringList &publishers, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDialog)
{
    ui->setupUi(this);

    // Заповнюємо QComboBox авторами і видавництвами
    ui->authorList->addItem("");  // Додаємо порожню опцію для авторів
    ui->authorList->addItems(authors);  // Додаємо список авторів
    ui->publisherList->addItem("");  // Додаємо порожню опцію для видавництв
    ui->publisherList->addItems(publishers);  // Додаємо список видавництв

    // Підключаємо сигнал для обробки натискання кнопок у діалоговому вікні
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SortDialog::handleButtonClicked);
}

// Деструктор діалогового вікна сортування
SortDialog::~SortDialog()
{
    delete ui;
}

// Метод для отримання вибраного автора
QString SortDialog::getAuthor() const {
    return ui->authorList->currentText();
}

// Метод для отримання вибраного видавництва
QString SortDialog::getPublisher() const {
    return ui->publisherList->currentText();
}

// Метод для отримання введеного року
QString SortDialog::getYear() const {
    return ui->yearLine->text();
}

// Метод для обробки натискання кнопок у діалоговому вікні
void SortDialog::handleButtonClicked(QAbstractButton *button) {
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);
    if (stdButton == QDialogButtonBox::Apply) {
        accept();  // Приймаємо зміни і закриваємо діалогове вікно
    } else if (stdButton == QDialogButtonBox::Cancel) {
        reject();  // Відхиляємо зміни і закриваємо діалогове вікно
    }
}
