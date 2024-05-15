#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class SortDialog;
}

class SortDialog: public QDialog {
    Q_OBJECT

public:
    explicit SortDialog(QWidget *parent = nullptr);
    ~SortDialog();

    QString getAuthor() const;
    QString getPublisher() const;
    QString getYear() const;

private:
    Ui::SortDialog *ui;
};

#endif // SORTDIALOG_H
