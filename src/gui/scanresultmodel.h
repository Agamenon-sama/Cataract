#ifndef SCANRESULTMODEL_H
#define SCANRESULTMODEL_H

#include <QAbstractTableModel>

#include "../Cataract/Cataract.h"

/**
 * @brief A model representation of the scan results to serve table views
 */
class ScanResultModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    // we have 4 properties to show so the number of columns is always 4
    const int numberOfColumns = 4;

    explicit ScanResultModel(QObject *parent = nullptr); ///< @brief constructor

    /**
     * @brief number of scan result available to show
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @brief number of columns in the table
     *
     * This number corresponds to the number of properties of this data
     *
     * This function simply returns numberOfColumns
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @brief returns the data represented by the model
     * @param index position of the data in the table meaning which row and column
     * @param role
     * @return data to be displayed by the view at that index
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /**
     * @brief define the titles of the columns
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /**
     * @brief update the model with new scan results
     * @param results new data
     */
    void setResults(const std::vector<Cataract::ScanResult> &results);

private:
    std::vector<Cataract::ScanResult> _scanResults; ///< stores the actual data the model represents
};

#endif // SCANRESULTMODEL_H
