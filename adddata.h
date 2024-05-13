#ifndef ADDDATA_H
#define ADDDATA_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QStandardPaths>
#include <QFileDialog>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QImageReader>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "client.h"


namespace Ui {
class adddata;
}

class adddata : public QWidget
{
    Q_OBJECT

public:
    explicit adddata(QWidget *parent = nullptr);
    ~adddata();

private slots:
    void on_SaveBtn_clicked();

    void on_CancelBtn_clicked();

    void on_Photolabel_linkActivated(const QString &link);

    void on_Server_clicked();

private:
    Ui::adddata *ui;
    QMessageBox *msg;
    void fnToResetUI();
    QString ImageFile;
    QString DataPath;
    bool m_isAllDataPresent();
    bool m_isAnyDataPresent();
    client *clientobj;
};

#endif // ADDDATA_H
