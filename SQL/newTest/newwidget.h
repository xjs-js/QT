#ifndef NEWWIDGET_H
#define NEWWIDGET_H

#include <QWidget>

namespace Ui {
class NewWidget;
}

class NewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewWidget(QWidget *parent = nullptr);
    ~NewWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewWidget *ui;
};

#endif // NEWWIDGET_H
