#ifndef WIDGET_H
#define WIDGET_H

#include <QColor>
#include <QList>
#include <QMouseEvent>
#include <QPair>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum RecordStatus{NeedCkPoints, ckPointsRecording, NeedClkPoint, clkPointRecording};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    RecordStatus status;

    QList<QPair<QPoint, QColor>> ckPoints;
    QPoint clkPoint;

    void recordBtnClicked();

    void mousePressEvent(QMouseEvent *event);

    void running();
};
#endif // WIDGET_H
