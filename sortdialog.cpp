#include "sortdialog.h"
#include "./ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDialog)  // This is correct if ui_sortdialog.h is correctly included
{
    ui->setupUi(this);  // This should work if all includes are correct
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SortDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SortDialog::reject);
}

SortDialog::~SortDialog()
{
    delete ui;  // Safe to delete if all is well
}

QString SortDialog::getAuthor() const {
    return ui->comboBoxAuthor->currentText();
}

QString SortDialog::getPublisher() const {
    return ui->comboBoxPublisher->currentText();
}

QString SortDialog::getYear() const {
    return ui->lineEditDate->text();  // Returning the text as a string
}

