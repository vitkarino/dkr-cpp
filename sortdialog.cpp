#include "sortdialog.h"
#include "./ui_sortdialog.h"

SortDialog::SortDialog(const QStringList &authors, const QStringList &publishers, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDialog)
{
    ui->setupUi(this);

    // Заповнюємо QComboBox авторами і видавництвами
    ui->authorList->addItem("");
    ui->authorList->addItems(authors);
    ui->publisherList->addItem("");
    ui->publisherList->addItems(publishers);

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SortDialog::handleButtonClicked);
}

SortDialog::~SortDialog()
{
    delete ui;
}

QString SortDialog::getAuthor() const {
    return ui->authorList->currentText();
}

QString SortDialog::getPublisher() const {
    return ui->publisherList->currentText();
}

QString SortDialog::getYear() const {
    return ui->yearLine->text();
}

void SortDialog::handleButtonClicked(QAbstractButton *button) {
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);
    if (stdButton == QDialogButtonBox::Apply) {
        accept();
    } else if (stdButton == QDialogButtonBox::Cancel) {
        reject();
    }
}
