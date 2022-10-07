#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    mes = new QMessageBox();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER="+ui->lineEdit->text()+";DATABASE="+ui->lineEdit_2->text()+";");
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());

    if (db.open()){
        mes->setText("Соединилось");
    } else{
        mes->setText("Соединение НЕ установлено");
    }
    mes->show();
}
