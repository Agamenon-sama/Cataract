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
    return 3; // we have 3 properties to show so the number of columns is always 3
}

QVariant ScanResultModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return QString("%1").arg(QString::fromStdString(_scanResults[index.row()].getAddress().getIp()));
        case 1:
            return QString("%1").arg(_scanResults[index.row()].getPort());
        case 2:
            return QString("%1")
                    .arg(QString::fromStdString(Cataract::scanStatusToString(_scanResults[index.row()].getStatus())));
        }
    }
    return QVariant();
}
