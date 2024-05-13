#include "viewdata.h"
#include "ui_viewdata.h"

viewdata::viewdata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewdata)
{
    ui->setupUi(this);
}

viewdata::~viewdata()
{
    delete ui;
}
