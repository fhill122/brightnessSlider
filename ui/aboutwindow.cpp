#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
