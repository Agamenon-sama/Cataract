#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QDateTime>

#include "../Cataract/Cataract.h"

#include "../utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);
    setWindowTitle("Cataract");
    setStyleSheet("QLabel {}");
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::on_btnScan_clicked()
{
    // get hostname
    std::string hostname = ui->lineHost->text().toStdString();
    if (hostname == "") {
        QMessageBox::critical(this, "no hostname", "No hostname was entered");
        return;
    }
    Cataract::IPAddress addr(hostname);

    // get ports
    std::string portsStr = ui->linePorts->text().toStdString();
    if (portsStr == "") {
        QMessageBox::critical(this, "no port", "No port was entered");
        return;
    }
    std::vector<uint16_t> ports;
    if(!argToPorts(portsStr, ports)) {
        QMessageBox::critical(this, "invalid ports", "The ports ranges you inputed are invalid");
        return;
    }

    // scanning
    ui->txtOutput->append(QString("The scan started at <font color=\"blue\">%1</font>").arg(QDateTime::currentDateTimeUtc().toString()));
    Cataract::TcpScanner scanner;

    auto results = scanner.portSweep(addr, ports);
    // auto result = scanner.singleScan(addr, std::stoi(port));
    for (auto result : results) {
        if (result.isOpen()) {
            ui->txtOutput->append(QString("The port %1/tcp is <font color=\"green\">open</font>").arg(result.getPort()));
        }
        else {
            ui->txtOutput->append(QString("The port %1/tcp is <font color=\"red\">closed</font>").arg(result.getPort()));
        }
    }

    ui->txtOutput->append("<font color=\"grey\">--------------------------</font>");
}

