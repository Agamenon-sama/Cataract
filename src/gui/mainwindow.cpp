#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

#include "../Cataract/Cataract.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);
    setWindowTitle("Learn");
    setStyleSheet("QLabel {}");
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::on_btnScan_clicked()
{
    std::string hostname = ui->lineHost->text().toStdString();
    if (hostname == "") {
        QMessageBox::critical(this, "no hostname", "No hostname was entered");
        return;
    }
    Cataract::IPAddress addr(hostname);

    std::string port = ui->linePorts->text().toStdString();
    if (port == "") {
        QMessageBox::critical(this, "no port", "No port was entered");
        return;
    }

    Cataract::TcpScanner scanner;
    if (scanner.singleScan(addr, std::stoi(port))) {
        QMessageBox::information(this, "scan result", "The port is open");
    }
    else {
        QMessageBox::information(this, "scan result", "The port is closed");
    }
}

