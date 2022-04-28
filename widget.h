#ifndef WIDGET_H
#define WIDGET_H

#include <QColor>
#include <QList>
#include <QMouseEvent>
#include <QPair>
#include <QWidget>

#include <QHotkey/qhotkey.h>

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

    QHotkey* hotkey;

    void recordBtnClicked();

    void addPoint();

    void running();
};
#endif // WIDGET_H
