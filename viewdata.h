#ifndef VIEWDATA_H
#define VIEWDATA_H

#include <QWidget>

namespace Ui {
class viewdata;
}

class viewdata : public QWidget
{
    Q_OBJECT

public:
    explicit viewdata(QWidget *parent = nullptr);
    ~viewdata();

private:
    Ui::viewdata *ui;
};

#endif // VIEWDATA_H
