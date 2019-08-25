#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// private members
private:
    Ui::MainWindow *ui;     // ui class
    QAction *hello;         // 标注
    QAction *bye;           // 取消标注

// private functions
private:
    void LoadXML();         // load xml
    void createActions();   // init create actions

private slots:
    void OnPushButtonClicked();             // 点击save按钮之后，保存内容到xml文件
    void ShowContextMenu(const QPoint &);   // 修改右击菜单
    void OnHello();                         // 标注-红
    void OnBye();                           // 取消标注-黑
};

#endif // MAINWINDOW_H
