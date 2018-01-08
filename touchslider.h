#ifndef TOUCHSLIDER_H
#define TOUCHSLIDER_H

#include <QSlider>
#include <QMouseEvent>


class TouchSlider : public QSlider
{
public:
    bool ignoreNextMove = false;

public:
    TouchSlider(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
};

#endif // TOUCHSLIDER_H
