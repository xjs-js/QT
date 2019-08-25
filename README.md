# QT

## textXML
打开程序一开始，textEdit会从xml文件中加载文字，用HTML格式。在打开后的界面中，用户可以选择标注其中的文字为红色或者取消标注。

textEdit保存HTML格式

```cpp
QString QTextEdit::toHtml() const;
void    QTextEdit::setHtml(const QString & text);
```

用户自定义菜单

```cpp
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
		...
    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textEdit, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));
    ...
}

void MainWindow::ShowContextMenu(const QPoint &pt)
{
    QMenu *menu = ui->textEdit->createStandardContextMenu();
    menu->addAction(hello);
    menu->addAction(bye);
    menu->exec(ui->textEdit->mapToGlobal(pt));
}
```

实现标注和取消标注

```cpp
void MainWindow::createActions()
{
    hello = new QAction(tr("hello"), this);
    connect(hello, SIGNAL(triggered()), this, SLOT(OnHello()));

    bye = new QAction(tr("bye"), this);
    connect(bye, SIGNAL(triggered()), this, SLOT(OnBye()));
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
```

## Minimum-QuickLauncher启动器

在windows右下角任务栏创建菜单，mac在右上角。

[参考🔗](https://blog.csdn.net/zhuyunfei/article/details/51433822)

主要用到QSystemTrayIcon，之后createActions()，createMenu()，就行了。

在macOS上dock栏图标不会自动隐藏，[解决方法](https://stackoverflow.com/questions/4718668/qt-c-on-mac-how-do-i-hide-my-dock-icon)；在生成的build文件夹下，找到Info.plist，增加一对keyvalue就行了。