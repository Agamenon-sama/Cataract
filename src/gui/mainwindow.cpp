#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QDateTime>
#include <QFile>

#include <chrono>

#include "../Cataract/Cataract.h"

#include "../utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);
    setWindowTitle("Cataract");

    // using dark theme by default
    setDarkTheme();

    // set model for the table of results
    _resultsModel = new ScanResultModel(nullptr);
    ui->tableResults->setModel(_resultsModel);

    // not sure if I can do these connects from Qt Designer but the good old way seemed simpler
    connect(ui->actionNative, SIGNAL(triggered()), this, SLOT(setNativeTheme()));
    connect(ui->actionDark, SIGNAL(triggered()), this, SLOT(setDarkTheme()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete _resultsModel;
}



void MainWindow::on_btnScan_clicked()
{
    // get hostname
    std::string hostname = ui->lineHost->text().toStdString();
    if (hostname == "") {
        QMessageBox::critical(this, "no hostname", "No hostname was entered");
        return;
    }
    sa_family_t addrType = AF_INET;
    if (ui->chkIpv6->isChecked()) addrType = AF_INET6;
    Cataract::IPAddress addr(hostname, addrType);

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
    ui->txtOutput->append(QString("Scanning %1 (%2)").arg(addr.getAddr().c_str(), addr.getIp().c_str()));
    Cataract::TcpScanner scanner;

    auto beginTimer = std::chrono::system_clock::now();
    auto results = scanner.portSweep(addr, ports);
    auto endTimer = std::chrono::system_clock::now();

    _resultsModel->setResults(results);

    for (const auto& result : results) {
        if (result.isOpen()) {
            ui->txtOutput->append(QString("The port %1/tcp is <font color=\"green\">open</font>").arg(result.getPort()));
        }
        else {
            ui->txtOutput->append(QString("The port %1/tcp is <font color=\"red\">closed</font>").arg(result.getPort()));
        }
    }
    ui->txtOutput->append(QString("Scan duration: <font color=\"green\">%1ms</font>")
                          .arg(std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - beginTimer).count()));

    ui->txtOutput->append("<font color=\"grey\">--------------------------</font>");
}

void MainWindow::setNativeTheme() {
    setStyleSheet("");
}

void MainWindow::setDarkTheme() {
    QFile style(":/main/styles/main.qss");
    if (style.open(QFile::ReadOnly)) {
        QTextStream in(&style);
        setStyleSheet(in.readAll());
        style.close();
    } else {
        QMessageBox::warning(this, "file reading", "Failed to load style file. The program will use the default style.");
    }
}

