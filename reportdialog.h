#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>

namespace Ui {
class reportDialog;
}

class reportDialog : public QDialog
{
    Q_OBJECT


public:
    explicit reportDialog(QWidget *parent = 0);
    ~reportDialog();
    QString results[15];
    int result_type[15];

    void update();

private:
    Ui::reportDialog *ui;
};

#endif // REPORTDIALOG_H
