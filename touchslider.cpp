#include "touchslider.h"
#include <Windows.h>
#include <QDebug>

TouchSlider::TouchSlider(QWidget *parent):QSlider(parent)
{

}

void TouchSlider::mouseMoveEvent(QMouseEvent *ev){
//    qDebug()<<"slider mouse move";

    if (ignoreNextMove){
        ignoreNextMove = false;
        return;
    }

    int toSet = minimum() + (maximum() - minimum())*ev->x()/width();
    setValue(toSet);
}

void TouchSlider::mousePressEvent(QMouseEvent *ev){
//    qDebug()<<"slider mouse press";
    int toSet = minimum() + (maximum() - minimum())*ev->x()/width();
    setValue(toSet);
}
