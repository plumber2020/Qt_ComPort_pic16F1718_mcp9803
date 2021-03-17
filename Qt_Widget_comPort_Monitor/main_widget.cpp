#include "main_widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setMinimumSize(500,200);

}

Widget::~Widget()
{
    delete ui;
}

