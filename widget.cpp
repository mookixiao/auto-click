#include "widget.h"
#include "./ui_widget.h"

#include <QCursor>
#include <QScreen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 成员变量
    status = NeedCkPoints;
    hotkey = new QHotkey(QKeySequence("ctrl+shift+a"), true, this);

    // 界面
    ui->ckPointsTextEdit->setReadOnly(true);
    ui->clkPointLineEdit->setReadOnly(true);

    // 信号与槽
    connect(ui->recordBtn, &QPushButton::clicked, this, &Widget::recordBtnClicked);
    connect(hotkey, &QHotkey::activated, this, &Widget::addPoint);
    connect(ui->runBtn, &QPushButton::clicked, this, &Widget::running);
}

Widget::~Widget()
{
    delete ui;

    delete hotkey;
}

void Widget::recordBtnClicked()
{
    if(status == NeedCkPoints) {
        ui->label->setText("正在记录检测点");
        ui->recordBtn->setText("停止记录检测点");
        status = ckPointsRecording;

        // 清空历史数据
        ckPoints.clear();
        ui->ckPointsTextEdit->clear();
        ui->clkPointLineEdit->clear();
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

void Widget::addPoint()
{
    if(status == ckPointsRecording) {
        QPoint pos = QCursor::globalPos();
        QScreen *screen = qApp->primaryScreen();
        QPixmap pixmap = screen->grabWindow(0, pos.x(), pos.y(), 1, 1);
        QColor color = pixmap.toImage().pixelColor(0, 0);

        ckPoints.append(QPair<QPoint, QColor>(pos, color));

        ui->ckPointsTextEdit->append(QString("(%1, %2) is (%3, %4, %5)")
                                     .arg(pos.x(), pos.y(), color.red(), color.green(), color.blue()));
    }
    else if(status == clkPointRecording) {
        clkPoint = event->globalPos();

        ui->clkPointLineEdit->setText(QString("(%1, %2)").arg(clkPoint.x(), clkPoint.y()));
    }
}

void Widget::running()
{
}


//#include "widget.h"
//#include "./ui_widget.h"

//#include <QDebug>
//#include <QScreen>
//#include <QString>
//#include <QTextBlock>
//#include <QThread>
//#include <QTime>

//#include <windows.h>

//Widget::Widget(QWidget *parent)
//    : QWidget(parent)
//    , ui(new Ui::Widget)
//{
//    ui->setupUi(this);

//    // 初始化界面
//    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::start);
//}

//Widget::~Widget()
//{
//    delete ui;
//}

//void Widget::start()
//{
////    QString qstrAll("");
////    QString qstrPlainText = ui->ckPointsTextEdit->toPlainText();
//    // 1.获取检测点
//    QTextDocument* pDocument = ui->ckPointsTextEdit->document();
//    QTextBlock block = pDocument->begin();
//    while (block.isValid() && block.layout()) {
//        QString qstrBlock = block.text();
//        QTextLayout* pLayout = block.layout();
//        int ctBlockLine = pLayout->lineCount();
//        for (int i = 0; i < ctBlockLine; ++i) {
//            QTextLine line = pLayout->lineAt(i);
//            int nStart = line.textStart();
//            int nLen = line.textLength();
//            QString qstrBlockLine = qstrBlock.mid(nStart, nLen);

////            qDebug() << qstrBlockLine;

//            QStringList strList = qstrBlockLine.split(',');
//            QPoint point(strList.at(0).toInt(), strList.at(1).toInt());
//            QColor rgb(strList.at(2).toInt(), strList.at(3).toInt(), strList.at(4).toInt());

////            qDebug() << point << rgb.red();

//            ckPoints.append(QPair<QPoint, QColor>(point, rgb));
//        }
//        block = block.next();
//    }

//    // 2.获取点击点
//    QStringList strList = ui->clkPointLineEdit->text().split(',');
//    clkPoint = QPoint(strList.at(0).toInt(), strList.at(1).toInt());

//    // 检测开始
//    QPixmap fullScreen;
//    QImage fullScreenImg;
//    QPoint point;
//    QColor color;

//    QScreen *pscreen = QApplication::primaryScreen();
//    while(1) {
//        fullScreen = pscreen->grabWindow(0, 0, 0, 1920, 1080);
//        fullScreenImg = fullScreen.toImage();

////        qDebug() << fullScreen.save(QString("E:\\迅雷下载\\") + QTime::currentTime().toString("HH-mm-ss") + ".png");

//        bool flag = true;
//        for(int i = 0; i < ckPoints.size(); ++i) {
//            point = ckPoints.at(i).first;
//            color = ckPoints.at(i).second;
//            if(!(fullScreenImg.pixelColor(point) == color)) {
//                flag = false;
//                break;;
//            }
//        }

//        if(flag) {
//            mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, clkPoint.x() * 65535 / 1920, clkPoint.y() * 65535 / 1080,0 ,0);  //移动到指定位置
//            mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);  //按下左键
//            mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);  //左键抬起
//        }

//        QThread::sleep(2);
//    }
//}
