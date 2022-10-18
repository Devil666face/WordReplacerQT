#include "database.h"

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = qApp->applicationDirPath();
    path.push_back("/database.db");
    db.setDatabaseName(path);
    if (db.open())  qDebug("database open");
    else qDebug("database not open");
}

QStringList database::get_template_names()
{
    QStringList template_names;
    query = new QSqlQuery(db);
    query->exec("SELECT name FROM Template;");
    while (query->next())
    {
        qDebug()<<query->value(0).toString();
        template_names.append(query->value(0).toString());
    }
    return template_names;
}

int database::get_id_for_template_name(QString template_name)
{
    query = new QSqlQuery(db);
    query->exec(QString("SELECT id FROM Template WHERE name = '%1';").arg(template_name));
    query->first();
    return query->value(0).toInt();
}

QSqlDatabase database::get_database()
{
    return db;
}

QVector <QVector<QString>> database::get_data_for_current_template_id(int template_id)
{
    QVector <QVector<QString>> data;
    query = new QSqlQuery(db);
    query->exec(QString("SELECT label, default_value, tag FROM Replace WHERE template_id=%1;").arg(template_id));
    while (query->next())
    {
        QVector <QString> row;
        row.append(query->value(0).toString());
        row.append(query->value(1).toString());
        row.append(query->value(2).toString());
        data.append(row);
    }
    return data;
}

void database::insert_data_for_replace(int template_id, QVector<QVector<QString> > data)
{
    foreach (auto row, data)
    {
        query->exec(QString("UPDATE Replace SET value='%1' WHERE tag='%2' AND template_id=%3;").arg(row[1]).arg(row[2]).arg(template_id));
        qDebug()<<QString("UPDATE Replace SET value='%1' WHERE tag='%2' AND template_id=%3;").arg(row[1]).arg(row[2]).arg(template_id);

    }
}


