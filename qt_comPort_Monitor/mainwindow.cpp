#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./widget/displaygroup_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    displayForm = new DisplayGroup_Form(this);
    ui->rootLayout_display->addWidget(displayForm);

    QString message_test("MCP9800:000; 70.2 LOW");
    displayForm->messageUpdate(message_test);
}

MainWindow::~MainWindow()
{
    delete ui;
}

