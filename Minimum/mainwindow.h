#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *mSysTrayIcon;
    QMenu *menu;
    QMenu *vivaldiMenu;
    QAction *vivaldi;
    QAction *aExit;
    QAction *vivaldiBBC;

private:
    void createActions();
    void createMenu();

private slots:
    void OnPushButtonClicked();
    void OnVivaldiOpenAction();
    void OnExitAction();
    void OnVivaldiBBC();
};



#endif // MAINWINDOW_H
