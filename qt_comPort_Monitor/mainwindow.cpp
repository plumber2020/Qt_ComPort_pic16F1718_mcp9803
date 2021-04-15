#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./widget/displaygroup_form.h"
#include "./widget/comportgroup_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    displayForm = new DisplayGroup_Form(this);
    ui->rootLayout_display->addWidget(displayForm);

    comportForm = new ComPortGroup_Form(this);
    ui->rootLayout_config->addWidget(comportForm);

    connect(comportForm,&ComPortGroup_Form::messageUpdated,
            displayForm,&DisplayGroup_Form::treatMessage);
    connect(comportForm,&ComPortGroup_Form::portDisactivated,
            displayForm,&DisplayGroup_Form::removeDeviceForm);

}

MainWindow::~MainWindow()
{
    delete ui;
}



