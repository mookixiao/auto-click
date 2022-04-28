#include "widget.h"
#include "./ui_widget.h"

#include <QScreen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 成员变量
    status = NeedCkPoints;

    // 界面
    ui->ckPointsTextEdit->setReadOnly(true);
    ui->clkPointLineEdit->setReadOnly(true);

    // 信号与槽
    connect(ui->recordBtn, &QPushButton::clicked, this, &Widget::recordBtnClicked);
    connect(ui->runBtn, &QPushButton::clicked, this, &Widget::running);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::recordBtnClicked()
{
    if(status == NeedCkPoints) {
        ui->label->setText("正在记录检测点");
        ui->recordBtn->setText("停止记录检测点");
        status = ckPointsRecording;
    }
    else if(status == ckPointsRecording) {
        ui->label->setText("等待记录点击点");
        ui->recordBtn->setText("开始记录点击点");
        status = ckPointsRecording;
    }
    else if(status == NeedClkPoint) {
        ui->label->setText("正在记录点击点");
        ui->recordBtn->setText("停止记录点击点");
        status = clkPointRecording;
    }
    else if(status == clkPointRecording) {
        ui->label->setText("检测点、点击点记录完毕，可以开始运行");
        ui->recordBtn->setText("重新记录检测点");
        status = NeedCkPoints;
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if(status == ckPointsRecording) {
            // 清空历史数据
            ckPoints.clear();
            ui->ckPointsTextEdit->clear();
            ui->clkPointLineEdit->clear();

            // 开始记录
            QPoint pos = event->globalPos();
            QScreen *screen = qApp->primaryScreen();
            QPixmap pixmap = screen->grabWindow(0, pos.x(), pos.y(), 1, 1);
            QColor color = pixmap.toImage().pixelColor(pos);

            ckPoints.append(QPair<QPoint, QColor>(pos, color));

            ui->ckPointsTextEdit->append(QString("(%1, %2) is (%3, %4, %5)")
                                         .arg(pos.x(), pos.y(), color.red(), color.green(), color.blue()));
        }
        else if(status == clkPointRecording) {
            clkPoint = event->globalPos();

            ui->clkPointLineEdit->setText(QString("(%1, %2)").arg(clkPoint.x(), clkPoint.y()));
        }
    }

    QWidget::mousePressEvent(event);
    event->ignore();
}

void Widget::running()
{

}
