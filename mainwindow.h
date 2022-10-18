#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QFileDialog>
#include <QStandardPaths>
#include "animatedlabel.h"
#include "database.h"
#include "replacer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    database db;
    QVector<QVector<QString> > current_data;

    void add_data_to_tableWidget_template(QVector <QVector<QString>> data);

    //buttons
    void initial_main_window();
    void create_button_master_template();
    void create_button_make_doc();

private slots:
    void on_pushButton_master_template();
    void on_pushButton_make_doc();
    void on_comboBox_template_name_currentTextChanged(const QString &arg1);
};
#endif // MAINWINDOW_H
