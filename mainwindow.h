#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "login.h"
#include "ui_login.h"
#include "addrecord.h"
#include "ui_addrecord.h"
#include "izmenenie.h"
#include "ui_izmenenie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Login* logwin;
    addrecord* dobzap;
    izmenenie* izm;

    int globid;
    int recId;
    int fl;

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void obt_ref_tab();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void CustomMenuReq(QPoint);

    void del_zap();

    void izm_zap();

    void viewRec_zap();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

signals:
    void sendId(int);

private:
    Ui::MainWindow *ui;
    //QSqlTableModel* model;
    QSqlQueryModel* model;
};
#endif // MAINWINDOW_H
