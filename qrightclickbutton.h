#ifndef QRIGHTCLICKBUTTON_H
#define QRIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class QRightClickButton : public QPushButton
{
    Q_OBJECT

public:
    QRightClickButton();

private slots:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void rightClicked();
    void leftClicked();

public slots:

};

#endif // QRIGHTCLICKBUTTON_H
