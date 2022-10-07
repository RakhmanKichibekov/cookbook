#include "izmenenie.h"
#include "ui_izmenenie.h"

izmenenie::izmenenie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::izmenenie)
{
    ui->setupUi(this);
}

izmenenie::~izmenenie()
{
    delete ui;
}

void izmenenie::obr_sendId(int aa)
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("select name_dish, id_recipe, id_cook, id_homeland from book where id_dish=?");
    query->bindValue(0, aa);

    if(query->exec())
    {
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        ui->lineEdit_2->setText(query->value(1).toString());
        ui->lineEdit_3->setText(QString::number(aa));
        ui->lineEdit_4->setText(query->value(2).toString());
        ui->lineEdit_5->setText(query->value(3).toString());
    }
}

void izmenenie::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("update book set name_dish=?,id_recipe=?,id_cook=?,id_homeland=? where id_dish=?");
    query->bindValue(0,ui->lineEdit->text());
    query->bindValue(1,ui->lineEdit_2->text());
    query->bindValue(2,ui->lineEdit_4->text());
    query->bindValue(3,ui->lineEdit_5->text());
    query->bindValue(4,ui->lineEdit_3->text());

    if (query->exec()){

    }
}
