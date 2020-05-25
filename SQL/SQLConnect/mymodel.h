#ifndef MYMODEL_H
#define MYMODEL_H

#include <map>
#include <vector>
#include <QObject>
#include <QSqlTableModel>

class MyModel : public QSqlTableModel
{
public:
    MyModel(QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex & index) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::DisplayRole) override;

    std::vector<int> getSelectedRows();
private:
    std::map<int, int> m_selectedRows; // ID, ROWID
};

#endif // MYMODEL_H
