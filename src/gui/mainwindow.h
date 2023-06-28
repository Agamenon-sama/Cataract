#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scanresultmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief main gui window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief runs the scanning procedure
     */
    void on_btnScan_clicked();
    /**
     * @brief sets the theme to the OS native look
     * 
     * unloads the qss theme to make Qt use the default OS look
     */
    void setNativeTheme();
    /**
     * @brief loads and sets the dark theme from the qss file
     */
    void setDarkTheme();

private:
    Ui::MainWindow *ui; ///< @brief contains the widgets
    ScanResultModel *_resultsModel; ///< @brief data representation of the scan results for the view
};
#endif // MAINWINDOW_H
