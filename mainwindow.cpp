#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial_main_window();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_data_to_tableWidget_template(QVector<QVector<QString> > data)
{
    ui->tableWidget_template->setRowCount(data.length());
//    ui->tableWidget_template->setColumnCount(data.first().length());
    ui->tableWidget_template->setColumnCount(2);
    for (int i=0;i<ui->tableWidget_template->rowCount();i++)
    {
        for (int j=0;j<ui->tableWidget_template->columnCount();j++)
        {
            ui->tableWidget_template->setItem(i,j, new QTableWidgetItem(data.value(i)[j]));
        }
    }
    current_data = data;

}

void MainWindow::initial_main_window()
{
    create_button_master_template();
    create_button_make_doc();
    ui->comboBox_template_name->addItems(db.get_template_names());
    QStringList vert_header;
    vert_header<<"Название"<<"Значение";
    ui->tableWidget_template->setHorizontalHeaderLabels(vert_header);
    ui->tableWidget_template->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::create_button_master_template()
{
    AnimatedLabel* button_master_template = new AnimatedLabel(this, ":/new/prefix1/icons/button_master_template.gif", "Открыть мастер шаблонов", 64, 64);
    ui->toolBar->addWidget(button_master_template);
    connect(button_master_template, SIGNAL(clicked()), SLOT(on_pushButton_master_template()));
}

void MainWindow::create_button_make_doc()
{
    AnimatedLabel* button_make_doc = new AnimatedLabel(this, ":/new/prefix1/icons/button_make_doc.gif", "Создать документ", 64, 64);
    ui->lay_make_doc->addWidget(button_make_doc);
    connect(button_make_doc, SIGNAL(clicked()), SLOT(on_pushButton_make_doc()));
}

void MainWindow::on_pushButton_master_template()
{
//    Открывать окно создания мастера шаблонов
}

void MainWindow::on_pushButton_make_doc()
{
    int current_template_id = db.get_id_for_template_name(ui->comboBox_template_name->currentText());
    for (int i = 0; i<ui->tableWidget_template->rowCount(); ++i)
    {
        current_data[i][1] = ui->tableWidget_template->item(i,1)->text();
    }
    db.insert_data_for_replace(current_template_id,current_data);
    QString file_name_to_save = QFileDialog::getSaveFileName(this,
                                                             QString("Создать %1").arg(ui->comboBox_template_name->currentText()),
                                                             QString(QStandardPaths::DesktopLocation),
                                                             tr("Word file (*.docx)"));

    replacer(current_template_id, file_name_to_save);
}

void MainWindow::on_comboBox_template_name_currentTextChanged(const QString &arg1)
{
    int current_template_id = db.get_id_for_template_name(arg1);
    QVector <QVector<QString>> data = db.get_data_for_current_template_id(current_template_id);
    add_data_to_tableWidget_template(data);
}
