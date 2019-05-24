#include "qrightclickbutton.h"

QRightClickButton::QRightClickButton() :
    QPushButton()
{
}

void QRightClickButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked();
    else
        emit leftClicked();
}

