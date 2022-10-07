#include "addrecord.h"
#include "ui_addrecord.h"

addrecord::addrecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addrecord)
{
    ui->setupUi(this);
}

addrecord::~addrecord()
{
    delete ui;
}

void addrecord::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("insert into book (name_dish, id_recipe, id_cook, id_homeland) values (:name,:id_recipe,:id_cook,:id_home)");
    query->bindValue(":name", ui->lineEdit->text());
    query->bindValue(":id_recipe", ui->lineEdit_2->text());
    query->bindValue(":id_cook", ui->lineEdit_3->text());
    query->bindValue(":id_home", ui->lineEdit_4->text());

    QMessageBox* mess = new QMessageBox();

    if(!query->exec()){
        mess->setText("Запрос составлен неверно");
        mess->show();
    }

    emit refresh_table();
}
