#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/Users/js/Desktop/workspace/QT/SQL/SchoolDB.db");
    if (m_db.open())
    {
        QStringList tables = m_db.tables();
        qDebug() << "######## Current Tables ########";
        qDebug() << tables;
        qDebug() << "######## Current Tables ########\n";

        m_model = new QSqlTableModel(this);


        m_mymodel = new MyModel(this);
        m_mymodel2 = new MyModel(this);
//        m_model->setTable("Students");
//        m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//        m_model->select();
        m_mymodel->setTable("Students");
        m_mymodel2->setTable("Students2");

        m_mymodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        m_mymodel2->setEditStrategy(QSqlTableModel::OnManualSubmit);

        m_mymodel->select();
        m_mymodel2->select();

        // sql第0列(StudentID)展示为ID
//        m_model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        // sql第1列(StudentName)展示为Name
//        m_model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        m_mymodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        m_mymodel->setHeaderData(1, Qt::Horizontal, tr("Name"));

        m_mymodel2->setHeaderData(0, Qt::Horizontal, tr("ID"));
        m_mymodel2->setHeaderData(1, Qt::Horizontal, tr("Name"));

//        ui->tableView->setModel(m_model);
        _view1 = new QTableView(this);
        _view2 = new QTableView(this);

        _view1->setModel(m_mymodel);
        _view1->resizeColumnsToContents();
        _view1->setSelectionBehavior(QAbstractItemView::SelectRows);

        _view2->setModel(m_mymodel2);
        _view2->resizeColumnsToContents();
        _view2->setSelectionBehavior(QAbstractItemView::SelectRows);

        ui->tabWidget->addTab(_view1, "Students");
        ui->tabWidget->addTab(_view2, "Students2");
    }
    else
    {
        qDebug() << "Database open failed.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto selectedRows = m_mymodel->getSelectedRows();

    auto it = selectedRows.begin();
    while (it != selectedRows.end())
    {
        qDebug() << "######## Import ########";
        qDebug() << "Selected Row: " << *it;

        QSqlRecord record = m_mymodel->record(*it-1);

        QString id = record.value(0).toString();
        QString name = record.value(1).toString();

        ui->textEdit->append("id: " + id + "; name: " + name);

        int rowCount = m_mymodel2->rowCount();
        qDebug() << "rowCount => " << rowCount;
        QSqlRecord newRecord = m_mymodel2->record();
        qDebug() << newRecord.fieldName(0);
        qDebug() << newRecord.fieldName(1);
        newRecord.setValue(0, 2);
        newRecord.setValue(2, "hello");
        newRecord.setGenerated()
        if (m_mymodel2->setRecord(1, newRecord))
        {
            m_mymodel2->submitAll();
        }

//        m_mymodel2->select();
        break;
        ++it;
        qDebug() << "######## Import ########\n";
    }


}
