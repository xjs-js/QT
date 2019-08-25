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

