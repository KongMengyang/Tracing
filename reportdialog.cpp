#include "reportdialog.h"
#include "ui_reportdialog.h"
#include <QDebug>
reportDialog::reportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reportDialog)
{
    ui->setupUi(this);
}

reportDialog::~reportDialog()
{
    delete ui;
}

void reportDialog::update()
{
    for(int i=0;i<15;i++)
    {
        int row =i;
        QTableWidgetItem *newitem=new QTableWidgetItem(results[i]);

        newitem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row,2,newitem);
        if(result_type[i]==1)
        {

            ui->tableWidget->setItem(row,3,new QTableWidgetItem("偏低"));
            ui->tableWidget->item(row,3)->setTextColor(QColor(0, 0, 255));
            ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
        else if(result_type[i]==2)
        {

            ui->tableWidget->setItem(row,3,new QTableWidgetItem("偏高"));
            ui->tableWidget->item(row,3)->setTextColor(QColor(255, 0, 0));
            ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
        else
        {
            ui->tableWidget->setItem(row,3,new QTableWidgetItem("正常"));
            ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
    }

}
