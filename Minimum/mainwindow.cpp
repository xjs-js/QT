#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <iostream>
//https://blog.csdn.net/zhuyunfei/article/details/51433822

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(OnPushButtonClicked()));

    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/icon/icon/1.png");
    mSysTrayIcon->setIcon(icon);

    createActions();
    createMenu();

    mSysTrayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    vivaldi = new QAction(QObject::trUtf8("打开"), this);
    connect(vivaldi, SIGNAL(triggered()), this, SLOT(OnVivaldiOpenAction()));

    aExit = new QAction(QObject::trUtf8("QUIT"), this);
    connect(aExit, SIGNAL(triggered()), this, SLOT(OnExitAction()));

    vivaldiBBC = new QAction(QObject::trUtf8("BBC"), this);
    connect(vivaldiBBC, SIGNAL(triggered()), this, SLOT(OnVivaldiBBC()));
}

void MainWindow::createMenu()
{
    menu = new QMenu(this);

    vivaldiMenu = menu->addMenu("Vivaldi");
    vivaldiMenu->addAction(vivaldi);
    vivaldiMenu->addSeparator();
    vivaldiMenu->addAction(vivaldiBBC);

    menu->addSeparator();
    menu->addAction(aExit);

    mSysTrayIcon->setContextMenu(menu);
}

void MainWindow::OnPushButtonClicked()
{
    this->hide();
    mSysTrayIcon->show();
}

void MainWindow::OnVivaldiOpenAction()
{
    QStringList arguments = (QStringList() << "Vivaldi.app");
    QProcess::startDetached("/Users/js/Program/qt/Minimum/start.sh", arguments);
}

void MainWindow::OnExitAction()
{
    exit(0);
}

void MainWindow::OnVivaldiBBC()
{
    QStringList arguments = (QStringList() << "Vivaldi.app" << "https://internetradiouk.com/bbc-2/");
    QProcess::startDetached("/Users/js/Program/qt/Minimum/start.sh", arguments);
}

