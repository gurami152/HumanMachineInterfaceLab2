#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int count = ui->spinBox->value();
    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(2);
    double res = 0;
    QString formula = "";
    double x = ui->doubleSpinBox_2->value();
    double valueToAdd = (ui->doubleSpinBox->value() - ui->doubleSpinBox_2->value())/count;
    for(int i =0; i<count; i++){
         try {
            if(ui->radioButton->isChecked()){
                formula = "y=5^(1+x^2) - 5^(1-x^2)";
                res = qPow(5,1+qPow(x,2))-qPow(5,1-qPow(x,2));
            }
            else if (ui->radioButton_2->isChecked()) {
                formula = "1+(1/1-sin^-1(2x+(8PI)/13))";
                res = 1+(1/(1-qPow(qSin(2*x+((8*M_PI)/13)),-1)));
            }
        }
        catch(std::exception &e){
            QMessageBox::critical(this, "Виключна ситуація","Виключна ситуація в точці" +QString::number(x));
        }
        QTableWidgetItem *itm = new QTableWidgetItem (tr("%1").arg(x));
        QTableWidgetItem *itm2 = new QTableWidgetItem (tr("%1").arg(res));
        ui->tableWidget->setItem(i,0,itm);
        ui->tableWidget->setItem(i,1,itm2);
        x+=valueToAdd;
    }
}

void MainWindow::on_doubleSpinBox_2_valueChanged(const QString &arg1)
{
    ui->doubleSpinBox->setMinimum(ui->doubleSpinBox_2->value());
}
