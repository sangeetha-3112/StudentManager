#include "client.h"
#include "ui_client.h"
#include "qmessagebox.h"


client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    ui->setupUi(this);
    serverAddressStr="192.168.1.123";
    serverAddress = QHostAddress(serverAddressStr);
    serverPort=123;
    ui->Status->setVisible(false);
}

client::~client()
{
    delete ui;
}

void client::on_pushButton_2_clicked()
{
    if(QMessageBox::question(this,"Question","Are you sure to exit?",(QMessageBox::Yes|QMessageBox::No))==QMessageBox::Yes)
        this->hide();
    ui->Status->setVisible(false);

}


void client::on_pushButton_clicked()
{

    ui->Status->setText("");
    socket.connectToHost(serverAddress, serverPort);

    // Check if the connection was successful
    if (socket.waitForConnected())
    {
        // Connection successful, send data to the server
        //QByteArray data = "Your data here";
        //socket.write(data);
        QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");

        db.setDatabaseName("students.db");
        QSqlQuery query;
        // Check Database Connection
        if (!db.open()) {
            qDebug() << "Error: Failed to open database:" << db.lastError().text();
            return; // Exit function to prevent further execution
        }

        // Check Query Execution
        if (!query.exec("SELECT * FROM students")) {
            qDebug() << "Error: Failed to execute query:" << query.lastError().text();
            return; // Exit function
        }

        // Data Retrieval and Formatting
        QJsonArray dataArray;
        while (query.next()) {
            // Check each field retrieval
            qDebug() << "Name:" << query.value("name").toString();
            qDebug() << "Roll Number:" << query.value("roll_number").toInt();
            qDebug() << "Standard:" << query.value("standard").toString();
            qDebug() << "Stream:" << query.value("Stream").toString();
            qDebug() << "Hobby:" << query.value("Hobby").toString();

            // Construct JSON object and add it to the array
            QJsonObject obj;
            obj["name"] = query.value("name").toString();
            obj["roll_number"] = query.value("roll_number").toInt();
            obj["standard"] = query.value("standard").toString();
            obj["Stream"] = query.value("Stream").toString();
            obj["Hobby"] = query.value("Hobby").toString();
            dataArray.append(obj);
        }


        // Data Transmission
        QJsonDocument doc(dataArray);
        QByteArray jsonData = doc.toJson();
        qDebug() << "Serialized JSON data:" << jsonData;
        socket.write(jsonData);
        socket.waitForBytesWritten();
        socket.disconnectFromHost();

        ui->Status->setText("Sent successfully");
        ui->Status->setVisible(true);

        // Wait for a response (if needed)
        if (socket.waitForReadyRead())
        {
            QByteArray response = socket.readAll();
            // Process response from the server
            ui->Status->setVisible(true);
            ui->Status->setText("Recieved Successfully");
        }
    }
     else
    {
        // Connection failed, handle error
        qDebug() << "Error: " << socket.errorString();
           ui->Status->setText("Failed");
        ui->Status->setVisible(true);
    }
}

