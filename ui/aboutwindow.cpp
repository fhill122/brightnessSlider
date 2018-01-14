#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDebug>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    ui->l_version->setText(QString("v%1.%2").arg(VERSION_MAJOR).arg(VERSION_MINOR));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowIcon(QIcon(iconFile));
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
