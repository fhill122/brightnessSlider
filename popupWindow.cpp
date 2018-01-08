#include "popupWindow.h"
#include "popupconfig.h"
#include "ui_popupWindow.h"
#include <Windows.h>
#include <tpcshrd.h>
#include <Dwmapi.h>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QGraphicsOpacityEffect>
#include <QGraphicsBlurEffect>

#include <QPainter>

#pragma comment(lib, "dwmapi.lib")

PopupWindow::PopupWindow(QWidget *parent) :
    QMainWindow(parent,Qt::Popup | Qt::FramelessWindowHint),
    ui(new Ui::PopupWindow)
{
    // ui
    animation = new QPropertyAnimation(this,"pos");
    animation->setDuration(PopupConfig::animationDuration);
    setAttribute(Qt::WA_TranslucentBackground, true);
    sliderRGB[0] = PopupConfig::slider_r; sliderRGB[1] = PopupConfig::slider_g; sliderRGB[2] = PopupConfig::slider_b;
    if (PopupConfig::sysColor){
        DWORD color = 0;
        BOOL opaque = FALSE;
        HRESULT hr = DwmGetColorizationColor(&color, &opaque);
        if (SUCCEEDED(hr)){
            sliderRGB[0] = GetBValue(color); sliderRGB[1] = GetGValue(color); sliderRGB[2] = GetRValue(color);
        }
    }
    RefreshUi();

    // set geometry
    SetGeometry();

    TogglePressAndHold(false);

    // signal connection beyond ui elements
    QObject::connect(QApplication::primaryScreen(), &QScreen::logicalDotsPerInchChanged, this, &PopupWindow::RefreshUi);

}


void PopupWindow::RefreshUi(){
    ui->setupUi(this);

    // brightness icon
    QPixmap p = QPixmap(PopupConfig::brightnessIcon);
    int iconSize = 1.*p.height()/3/96*QApplication::primaryScreen()->logicalDotsPerInch();
    ui->brightnessIcon->setPixmap( p.scaledToHeight( iconSize , Qt::SmoothTransformation)  );

    // set slider height
    int grooveHeight = 1.* PopupConfig::grooveHeight /96*QApplication::primaryScreen()->logicalDotsPerInch();
    QString sliderStyle =
            "QSlider::groove:horizontal{"
                "border: none;"
                "height: %1px;"
            "}"

            "QSlider::sub-page{"
                "background: rgb(%2, %3, %4);"
            "}"

            "QSlider::add-page{"
                "background: rgb(80, 80, 80);"
            "}"

            "QSlider::handle:horizontal {"
                "background: white;"
                "border: none;"
                "width: %5px;"
                "margin: -%6px 0;"
            "}"
            ;
    ui->brightnessSlider->setStyleSheet( sliderStyle.arg(
        QString::number(grooveHeight), QString::number(sliderRGB[0]), QString::number(sliderRGB[1]), QString::number(sliderRGB[2]),
        QString::number((int)(1.25*grooveHeight)), QString::number((int)(0.25*grooveHeight))
    ) );

    // make time remaining label semi transparent
//    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect(ui->timeLabel);
//    effect->setOpacity(PopupConfig::timeLabel_a);
//    ui->timeLabel->setGraphicsEffect(effect);

    //TODO blur effect. issue: all widgets are blurred but not the background
    // ui->centralWidget->setGraphicsEffect(new QGraphicsBlurEffect(ui->centralWidget));

    // signal connection in this ui
    QObject::connect(ui->brightnessSlider, &QSlider::valueChanged, [=](int value){brightnessControl.setBrightness(value);} );

    qDebug()<<"UI refreshed!";
}

// set popup window geometry according to the current dpi
void PopupWindow::SetGeometry(){
    int screenH = QApplication::desktop()->availableGeometry().height();
    int screenW = QApplication::desktop()->availableGeometry().width();
    int dpi = QApplication::primaryScreen()->logicalDotsPerInch();
    int windowH = PopupConfig::WINDOW_H * dpi/96;
    int windowW = PopupConfig::WINDOW_W * dpi/96;

    setGeometry(screenW - windowW, screenH - windowH, windowW, windowH);
    qDebug()<<"Geometry Set: h="<<windowH <<", real="<<height();
}

// along with TogglePressAndHold, used to disable the press and hold touch gesture
bool PopupWindow::nativeEvent(const QByteArray & , void * message, long * result) {

    MSG *msg = static_cast<MSG*>(message);
    if (msg->message == WM_TABLET_QUERYSYSTEMGESTURESTATUS) {
        *result = TABLET_DISABLE_PRESSANDHOLD;
        return true;
    }
    return false;
}

// Toggle the press and hold gesture for the given window
bool PopupWindow::TogglePressAndHold(bool enable)
{
    HWND hWnd = (HWND)this->winId();
    // The atom identifier and Tablet PC atom
    ATOM atomID = 0;
    LPCTSTR tabletAtom = (LPCTSTR) "MicrosoftTabletPenServiceProperty";

    // Get the Tablet PC atom ID
    atomID = GlobalAddAtom(tabletAtom);

    // If getting the ID failed, return false
    if (atomID == 0){
        return false;
    }

    // Enable or disable the press and hold gesture
    if (enable){
        return RemoveProp(hWnd, tabletAtom);
    }
    else{
        return SetProp(hWnd, tabletAtom, (HANDLE)1);
    }
}

void PopupWindow::Popup(QSystemTrayIcon::ActivationReason reason){
    if (reason != QSystemTrayIcon::Trigger) return;

    int currentBrightness = brightnessControl.getCurrentBrightness(true);
    qDebug() << "current brightness: " << currentBrightness;
    if (currentBrightness != -1){
        ui->brightnessSlider->setValue(currentBrightness);
    }

    SetGeometry();
    animation->setStartValue( QPoint(x()+width()/3,y()) );
    animation->setEndValue( QPoint(x(),y()) );
    animation->start();
    ui->brightnessSlider->ignoreNextMove=true;
    show();
}

void PopupWindow::UpdateBatteryInfo(_SYSTEM_POWER_STATUS powerStatus){
//    qDebug()<<powerStatus.BatteryLifeTime/60;
}


void PopupWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.fillRect(QRectF(0, 0, width(), height()), QColor(PopupConfig::background_r,PopupConfig::background_g,PopupConfig::background_b,255*PopupConfig::background_a));

}

PopupWindow::~PopupWindow(){
    delete ui;
}
