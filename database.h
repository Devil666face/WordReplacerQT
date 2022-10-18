#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>

class database
{
public:
    database();
    QSqlTableModel *model;

    QStringList get_template_names();
    int get_id_for_template_name(QString template_name);
    QSqlDatabase get_database();
    QVector <QVector<QString>> get_data_for_current_template_id(int template_id);
    void insert_data_for_replace(int template_id, QVector <QVector<QString>> data);

private:
    QSqlDatabase db;
    QSqlQuery *query;
};

#endif // DATABASE_H
