#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void timerEvent(QTimerEvent *event) override;
signals:

};

#endif // DISPLAYWIDGET_H
