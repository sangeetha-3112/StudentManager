#include "adddata.h"
#include "ui_adddata.h"
#include "qmessagebox.h"
#include "QDebug"
adddata::adddata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adddata)
{
    ui->setupUi(this);
    msg=new QMessageBox();
    clientobj=new client();
    QRegularExpression alphabeticRegex("[a-zA-Z]*");
    QRegularExpression digitRegex("\\b(?:[1-9][0-9]?|100)\\b");
    // Create a validator with the regular expression pattern
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(alphabeticRegex, this);
    QRegularExpressionValidator *validator_digit = new QRegularExpressionValidator(digitRegex, this);
    // Set the validator for the QLineEdit
    ui->NameEdit->setValidator(validator);
    ui->HobbyEdit->setValidator(validator);
    ui->RollEdit->setValidator(validator_digit);
    ui->warninglabel->setVisible(false);
}

adddata::~adddata()
{
    delete ui;
}

void adddata::fnToResetUI(){
    ui->NameEdit->clear();
    ui->ClassBox->setCurrentIndex(0);
    ui->RollEdit->clear();
    ui->streamBox->setCurrentIndex(0);
    ui->HobbyEdit->clear();
    ui->Photolabel->setText("<a href=\"https://www.example.com\">Click here</a> to upload");
}

bool adddata::m_isAllDataPresent(){
    QString Name=ui->NameEdit->text();
    int RollNo=ui->RollEdit->text().toInt();
    QString Class=ui->ClassBox->currentText();
    QString Stream=ui->streamBox->currentText();
    QString Hobby=ui->HobbyEdit->text();
    //QImageReader reader(ImageFile);
    if(Name.isEmpty()||!RollNo||Class.isEmpty()||Stream.isEmpty()||Hobby.isEmpty()||ImageFile.isEmpty())
        return false;
    return true;
}

bool adddata::m_isAnyDataPresent(){
    QString Name=ui->NameEdit->text();
    int RollNo=ui->RollEdit->text().toInt();
    QString Class=ui->ClassBox->currentText();
    QString Stream=ui->streamBox->currentText();
    QString Hobby=ui->HobbyEdit->text();
    //QImageReader reader(ImageFile);
    if(!Name.isEmpty()||RollNo||!Hobby.isEmpty()||!ImageFile.isEmpty())
        return true;
    return false;
}


void adddata::on_SaveBtn_clicked()
{
    QString Name=ui->NameEdit->text();
    int RollNo=ui->RollEdit->text().toInt();
    QString Class=ui->ClassBox->currentText();
    QString Stream=ui->streamBox->currentText();
    QString Hobby=ui->HobbyEdit->text();
    if(!m_isAllDataPresent())
       QMessageBox::question(this, "Information", "Please provide all the details",QMessageBox::Ok);
    else{
       /* QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString folderName = "StudentDetails"; // Name of the folder on desktop

        // Construct the directory path
        QString dirPath = desktopPath + QDir::separator() + folderName;
         // Create the directory if it doesn't exist
         QDir dir(dirPath);
         if (!dir.exists()) {
             dir.mkpath(dirPath);
         }

         // Construct the file path
         QString filePath = dirPath + QDir::separator() + "student_details.ini";

         // Create QSettings object with INI format
         QSettings settings(filePath, QSettings::IniFormat);

         // Write student details (same as before)
         settings.beginGroup(Name);
         settings.setValue("Name", Name);
         settings.setValue("RollNumber", RollNo);
         settings.setValue("Class", Class);
         settings.setValue("Stream", Stream);
         settings.setValue("Hobby", Hobby);
         settings.setValue("PhotoPath", ImageFile);
         settings.endGroup();*/
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("students.db");

        // Open the database
        if (!db.open()) {
            qDebug() << "Error: Failed to open database:" << db.lastError().text();

        }

        // Create a table to store student information
        QSqlQuery query(db); // Pass the database connection to the query
        if (!query.exec("CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, roll_number INTEGER, standard TEXT, Stream TEXT, Hobby TEXT)")) {
            qDebug() << "Error: Failed to create table:" << query.lastError().text();

        }

        // Insert data into the table
        QString insertQuery = QString("INSERT INTO students (name, roll_number, standard, Stream, Hobby) VALUES ('%1', %2, '%3', '%4', '%5')")
                                      .arg(Name).arg(RollNo).arg(Class).arg(Stream).arg(Hobby);
        if (!query.exec(insertQuery)) {
            qDebug() << "Error: Failed to insert data into table:" << query.lastError().text();

        }
qDebug()<<insertQuery;
        // Close the database connection
        db.close();



         QMessageBox::question(this, "Information", "Data has been successfully saved",QMessageBox::Ok);
         fnToResetUI();
    }

}


void adddata::on_CancelBtn_clicked()
{
    if(m_isAnyDataPresent()){
    if (QMessageBox::question(this, "Warning", "Are you sure you want to clear the fields?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        // User clicked Yes, handle accordingly
        fnToResetUI();
        //this->hide();
    }
    else
        this->show();
    }
    else
        QMessageBox::information(this,"Information", "Nothing to delete",QMessageBox::Ok);

}


void adddata::on_Photolabel_linkActivated(const QString &link)
{
    QString DesktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    ImageFile = QFileDialog::getOpenFileName(this,tr("Image File"),DesktopPath,tr("Image Files(*.jpg)"));
    if(ImageFile.isEmpty())
        return;
    QImageReader reader(ImageFile);
      QSize imageSize = reader.size();
      int requiredWidth = 366; // Example required dimensions
      int requiredHeight = 435;

      // Check if the image dimensions match the required dimensions
      if (imageSize.width() == requiredWidth && imageSize.height() == requiredHeight) {
          // Display the image in the QLabel
          QPixmap pixmap(ImageFile);
          pixmap = pixmap.scaled(ui->Photolabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
          ui->Photolabel->setPixmap(pixmap);
          ui->warninglabel->setText("");
          ui->warninglabel->setVisible(false);
      }
      else{
          ui->warninglabel->setVisible(true);
          ui->warninglabel->setText("Upload Failed");
          ImageFile="";
      }
}


void adddata::on_Server_clicked()
{
    clientobj->show();
}

