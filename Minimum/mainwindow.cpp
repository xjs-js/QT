#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>

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
    vivaldi = new QAction(QObject::trUtf8("Vivaldi"), this);
    connect(vivaldi, SIGNAL(triggered()), this, SLOT(OnVivaldiAction()));

    aExit = new QAction(QObject::trUtf8("QUIT"), this);
    connect(aExit, SIGNAL(triggered()), this, SLOT(OnExitAction()));

}

void MainWindow::createMenu()
{
    menu = new QMenu(this);
    menu->addAction(vivaldi);
    menu->addAction(aExit);
//    menu->addSeparator();
    mSysTrayIcon->setContextMenu(menu);
}

void MainWindow::OnPushButtonClicked()
{
    this->hide();
    mSysTrayIcon->show();
}

void MainWindow::OnVivaldiAction()
{
    QStringList arguments = (QStringList() << "Vivaldi.app");
    QProcess::startDetached("/Users/js/Program/qt/Minimum/start.sh", arguments);
}

void MainWindow::OnExitAction()
{
    exit(0);
}
