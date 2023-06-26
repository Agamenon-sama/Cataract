#ifndef SCANRESULTMODEL_H
#define SCANRESULTMODEL_H

#include <QAbstractTableModel>

#include "../Cataract/Cataract.h"

class ScanResultModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    // we have 4 properties to show so the number of columns is always 4
    const int numberOfColumns = 4;

    explicit ScanResultModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setResults(const std::vector<Cataract::ScanResult> &results);

private:
    std::vector<Cataract::ScanResult> _scanResults;
};

#endif // SCANRESULTMODEL_H
