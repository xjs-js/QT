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
    QAction *vivaldi;
    QAction *aExit;
private:
    void createActions();
    void createMenu();

private slots:
    void OnPushButtonClicked();
    void OnVivaldiAction();
    void OnExitAction();
};



#endif // MAINWINDOW_H
