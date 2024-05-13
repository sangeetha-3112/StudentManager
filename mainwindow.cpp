#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addobj=new adddata();
    viewobj=new viewdata();
   // stackedWidget = findChild<QStackedWidget*>("stackedWidget");
   // addDataIndex = stackedWidget->addWidget(addobj);
   // viewDataIndex=stackedWidget->addWidget(viewobj);

    ui->stackedWidget->addWidget(addobj);
    ui->stackedWidget->addWidget(viewobj);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(addobj));
//            if (stackedWidget)
//                stackedWidget->setCurrentIndex(addDataIndex);
//     stackedWidget->show();

}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(viewobj));
//    if (stackedWidget)
//        stackedWidget->setCurrentIndex(viewDataIndex);
//    stackedWidget->show();
}

