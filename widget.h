#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>
#include "math.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setImages();
    QColor* HSVtoRGB(QColor*);
protected:
    virtual void resizeEvent(QResizeEvent * re);
private:
    Ui::Widget *ui;
    int ax,ay,bx,by;
    double Pi = 3.1415;
    double k;
    QImage Apic;
    QImage Bpic;
};
#endif // WIDGET_H
