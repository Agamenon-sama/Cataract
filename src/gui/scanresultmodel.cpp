#include "scanresultmodel.h"

ScanResultModel::ScanResultModel(QObject *parent)
    : QAbstractTableModel{parent}
{
}

void ScanResultModel::setResults(const std::vector<Cataract::ScanResult> &results) {
    // reset model to inform the view that the number of elements
    // has changed.
    // use beginInsertRows() if you decide to insert new elements
    // and keep the old ones
    beginResetModel();
        _scanResults = results;
    endResetModel();
}

int ScanResultModel::rowCount(const QModelIndex&) const {
    return _scanResults.size(); // each row is an element in the results
}

int ScanResultModel::columnCount(const QModelIndex&) const {
    return numberOfColumns;
}

QVariant ScanResultModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return QString("%1").arg(QString::fromStdString(_scanResults[index.row()].getAddress().getAddr()));
        case 1:
            return QString("%1").arg(QString::fromStdString(_scanResults[index.row()].getAddress().getIp()));
        case 2:
            return QString("%1").arg(_scanResults[index.row()].getPort());
        case 3:
            return QString("%1")
                    .arg(QString::fromStdString(Cataract::scanStatusToString(_scanResults[index.row()].getStatus())));
        }
    }
    return QVariant();
}

QVariant ScanResultModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return QString("Address");
        case 1: return QString("IP Address");
        case 2: return QString("Port");
        case 3: return QString("Scan Status");
        }
    }
    return QVariant();
}
