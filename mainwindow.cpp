#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CustomMenuReq(QPoint)));
    fl = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    logwin = new Login();
    logwin->show();
}

void MainWindow::on_pushButton_clicked()
{
    fl=1;
    //model = new QSqlTableModel();
    model = new QSqlQueryModel();
    //model->setTable("book");
    model->setQuery("select * from book");
    //model->select();

    model->setHeaderData(0, Qt::Horizontal,"Номер блюда");
    model->setHeaderData(1, Qt::Horizontal,"Название блюда");
    model->setHeaderData(2, Qt::Horizontal,"Номер рецепта");
    model->setHeaderData(3, Qt::Horizontal,"Номер повара");
    model->setHeaderData(4, Qt::Horizontal,"Номер родины");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    dobzap = new addrecord();
    connect(dobzap, SIGNAL(refresh_table()), this, SLOT(obt_ref_tab()));
    dobzap->show();
}

void MainWindow::obt_ref_tab(){
    on_pushButton_clicked();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_nom;
    temp_nom = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    ui->lineEdit->setText(QString::number(temp_nom));

    QSqlQuery* query = new QSqlQuery();
    query->prepare("select name_dish, id_recipe, id_cook, id_homeland from book where id_dish=:id");
    query->bindValue(":id", temp_nom);
    if (query->exec()){
        query->next();
        ui->lineEdit_2->setText(query->value(0).toString());
        ui->lineEdit_3->setText(query->value(1).toString());
        ui->lineEdit_4->setText(query->value(2).toString());
        ui->lineEdit_5->setText(query->value(3).toString());
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("update book set name_dish=?,id_recipe=?,id_cook=?,id_homeland=? where id_dish=?");
    query->bindValue(0, ui->lineEdit_2->text());
    query->bindValue(1, ui->lineEdit_3->text());
    query->bindValue(2, ui->lineEdit_4->text());
    query->bindValue(3, ui->lineEdit_5->text());
    query->bindValue(4, ui->lineEdit->text());

    if (query->exec())
    {
       on_pushButton_clicked();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("delete from book where id_dish=?");
    query->bindValue(0, ui->lineEdit->text());

    if (query->exec())
    {
       on_pushButton_clicked();
    }
}

void MainWindow::CustomMenuReq(QPoint pos)
{
    if(fl==1) {
        QModelIndex index = ui->tableView->indexAt(pos);
        globid = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
        recId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toInt();

        QMenu* menu = new QMenu(this);
        QAction* izm = new QAction("Изменить", this);
        connect(izm, SIGNAL(triggered()), this, SLOT(izm_zap()));

        QAction* ud = new QAction("Удалить", this);
        connect(ud, SIGNAL(triggered()), this, SLOT(del_zap()));

        QAction* viewRec = new QAction("Показать рецепт", this);
        connect(viewRec, SIGNAL(triggered()), this, SLOT(viewRec_zap()));

        menu->addAction(izm);
        menu->addAction(ud);
        menu->addAction(viewRec);
        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}
void MainWindow::del_zap(){
    QSqlQuery* query = new QSqlQuery();

    query->prepare("delete from book where id_dish=?");
    query->bindValue(0, globid);
    if (query->exec()){
        on_pushButton_clicked();
    }
}

void MainWindow::izm_zap()
{
    izm = new izmenenie();
    connect(this, SIGNAL(sendId(int)), izm, SLOT(obr_sendId(int)));
    emit sendId(globid);
    izm->show();
    disconnect(this, SIGNAL(sendId(int)), izm, SLOT(obr_sendId(int)));
}

void MainWindow::viewRec_zap()
{
    QSqlQuery* query = new QSqlQuery();
    //query->prepare("select * from recipes where id_recipe=(select id_recipe from book where id_dish=?)");
    model->setQuery("select * from recipes where id_recipe=(select id_recipe from book where id_dish=3)");
    query->bindValue(0,globid);

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}


void MainWindow::on_pushButton_5_clicked()
{
    fl=1;
    model = new QSqlQueryModel();
    model->setQuery("SELECT cook.position_on_the_kitchen, cook.work_experience, CASE WHEN book.id_cook=1 THEN 'Igor' WHEN book.id_cook>1 THEN 'No Igor' ELSE 'error' END name_cook FROM book INNER JOIN cook on book.id_cook=cook.id_cook");

    model->setHeaderData(0, Qt::Horizontal,"Должность на кухне");
    model->setHeaderData(1, Qt::Horizontal,"Стаж работы");
    model->setHeaderData(2, Qt::Horizontal,"Имя");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    fl=1;
    model = new QSqlQueryModel();
    model->setQuery("SELECT id_homeland from homeland_dish where name_homeland='Греция' ");

    model->setHeaderData(0, Qt::Horizontal,"id родины");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    fl=1;
    model = new QSqlQueryModel();
    model->setQuery("SELECT book.name_dish id_cook FROM book,cook GROUP BY cook.id_cook, book.id_dish,book.name_dish HAVING COUNT(book.id_dish) = cook.id_cook;");

    model->setHeaderData(0, Qt::Horizontal,"Название блюда где количество его id  равно id повара");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_8_clicked()
{
    fl=1;
    model = new QSqlQueryModel();
    model->setQuery("SELECT cook.name_cook FROM cook WHERE id_cook = ANY (SELECT id_cook FROM recipes where work_experience=5);");

    model->setHeaderData(0, Qt::Horizontal,"Имена поваров");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    fl=1;
    model = new QSqlQueryModel();
    model->setQuery("select * from cook");

    model->setHeaderData(0, Qt::Horizontal,"Номер повара");
    model->setHeaderData(1, Qt::Horizontal,"имя повара");
    model->setHeaderData(2, Qt::Horizontal,"стаж работы");
    model->setHeaderData(3, Qt::Horizontal,"должность на кухне");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_10_clicked()
{
    fl=1;
    model = new QSqlQueryModel();
    model->setQuery("select * from recipes");

    model->setHeaderData(0, Qt::Horizontal,"Номер рецепта");
    model->setHeaderData(1, Qt::Horizontal,"Название рецепта");
    model->setHeaderData(2, Qt::Horizontal,"Метод приготовления");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_11_clicked()
{
    fl=1;
    model = new QSqlQueryModel();
    model->setQuery("select * from homeland_dish");

    model->setHeaderData(0, Qt::Horizontal,"Номер родины");
    model->setHeaderData(1, Qt::Horizontal,"Название родины");
    model->setHeaderData(2, Qt::Horizontal,"Первое место приготовления");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}
