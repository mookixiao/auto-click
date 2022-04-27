#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化界面

    // 初始化信号与槽
    connect(ui->recordBtn, &QPushButton::clicked, this, &Widget::recordStart);
    connect(ui->exitBtn, &QPushButton::clicked, this, &Widget::close);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::recordStart()
{
    ui->ckPointsTextEdit->clear();


}
