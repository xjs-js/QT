#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pugixml.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textEdit, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(OnPushButtonClicked()));

    LoadXML();
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadXML()
{
    pugi::xml_document doc;
    QString path = "/Users/js/Program/qt/testXML/test.xml";
    pugi::xml_parse_result result = doc.load_file(path.toStdString().c_str(), pugi::parse_full, pugi::encoding_auto);

    if (result)
    {
        pugi::xml_node root = doc.child("root");
        pugi::xml_node text = root.child("text");
        QString str = QString(text.text().get());
        ui->textEdit->setHtml(str.toStdString().c_str());
    }
}

void MainWindow::createActions()
{
    hello = new QAction(tr("hello"), this);
    connect(hello, SIGNAL(triggered()), this, SLOT(OnHello()));

    bye = new QAction(tr("bye"), this);
    connect(bye, SIGNAL(triggered()), this, SLOT(OnBye()));
}

void MainWindow::OnPushButtonClicked()
{
    pugi::xml_document doc;
    QString path = "/Users/js/Program/qt/testXML/test.xml";
    pugi::xml_parse_result result = doc.load_file(path.toStdString().c_str(), pugi::parse_full, pugi::encoding_auto);

    if (result)
    {
        pugi::xml_node root = doc.child("标注");

        pugi::xml_node text = root.child("取消标注");
        QString str = ui->textEdit->toHtml();
        text.text().set(str.toStdString().c_str());
    }
    doc.save_file(path.toStdString().c_str());
}

void MainWindow::ShowContextMenu(const QPoint &pt)
{
    QMenu *menu = ui->textEdit->createStandardContextMenu();
    menu->addAction(hello);
    menu->addAction(bye);
    menu->exec(ui->textEdit->mapToGlobal(pt));
}

void MainWindow::OnHello()
{
    QTextCharFormat fmt;
    fmt.setForeground(Qt::red);

    QTextCursor cursor(ui->textEdit->document());
    ui->textEdit->setCurrentCharFormat(fmt);
}

void MainWindow::OnBye()
{
    QTextCharFormat fmt;
    fmt.setForeground(Qt::black);

    QTextCursor cursor(ui->textEdit->document());
    ui->textEdit->setCurrentCharFormat(fmt);
}
