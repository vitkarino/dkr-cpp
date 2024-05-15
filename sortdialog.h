#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QDialogButtonBox>
#include <QAbstractButton>

namespace Ui {
class SortDialog;
}

class SortDialog: public QDialog {
    Q_OBJECT

public:
    explicit SortDialog(const QStringList &authors, const QStringList &publishers, QWidget *parent = nullptr);
    ~SortDialog();

    QString getAuthor() const;
    QString getPublisher() const;
    QString getYear() const;

private slots:
    void handleButtonClicked(QAbstractButton *button);

private:
    Ui::SortDialog *ui;
};

#endif // SORTDIALOG_H
