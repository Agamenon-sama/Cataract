#ifndef SCANRESULTMODEL_H
#define SCANRESULTMODEL_H

#include <QAbstractTableModel>

#include "../Cataract/Cataract.h"

class ScanResultModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ScanResultModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setResults(const std::vector<Cataract::ScanResult> &results);

private:
    std::vector<Cataract::ScanResult> _scanResults;
};

#endif // SCANRESULTMODEL_H
