#include "mymodel.h"
#include <QDebug>

MyModel::MyModel(QObject *parent)
    : QSqlTableModel(parent)
{

}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0)
    {
//        return QSqlQueryModel::flags(index) | Qt::ItemIsUserCheckable;
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    return QSqlQueryModel::flags(index);
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    // 第0列可以checkable
    if (index.column() == 0 && role == Qt::CheckStateRole)
    {
        QString id = QSqlQueryModel::data(index, Qt::DisplayRole).toString().trimmed();
        // 找到
        if (m_selectedRows.find(id.toInt()) != m_selectedRows.end())
        {
            return QVariant::fromValue<int>(Qt::Checked);
        }
        else
        {
            return QVariant::fromValue<int>(Qt::Unchecked);
        }
    }

    return QSqlQueryModel::data(index, role);
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "#### Data ####";
    qDebug() << QString("%1, %2 => %3\n").arg(QString::number(index.row()), QString::number(index.column()), QSqlQueryModel::data(index, Qt::DisplayRole).toString());
    if (index.column() == 0 && role == Qt::CheckStateRole)
    {
        QString id = QSqlQueryModel::data(index, Qt::DisplayRole).toString().trimmed();
        if (value.toInt() == Qt::Checked)
        {
            m_selectedRows.insert(std::make_pair(id.toInt(), index.row()));
        }
        else
        {
            auto it = m_selectedRows.find(id.toInt());
            if (it != m_selectedRows.end())
            {
                m_selectedRows.erase(it);
            }
        }
    }

    return QSqlQueryModel::setData(index, value, role);
}

std::vector<int> MyModel::getSelectedRows()
{
    std::vector<int> rows;
    auto it = m_selectedRows.begin();
    while (it != m_selectedRows.end())
    {
        rows.push_back(it->first);
        ++it;
    }

    return rows;
}



