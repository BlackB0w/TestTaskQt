#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ax = 4000;
    ay = 4000;
    bx = 2000;
    by = 2000;

    k = 0.002;
    setImages();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setImages(){
    // double A[ax][ay];
    // double B[bx][by];
    std::vector< std::vector<double> > A(ay, std::vector<double>(ax, 0.0));
    std::vector< std::vector<double> > B(by, std::vector<double>(bx, 0.0));

    int proportion = bx/ax;
    for (int i = 0; i < ax; i++)
        for (int j = 0; j < ay; j++)
            A[i][j] = cos(pow(k*i,2) + pow(k*j,2));
    for (int i = 0; i < ax; i++)
        for(int j = 0; j < ay; j++){
            int x = j*cos(i) * proportion;
            int y = j*sin(i) * proportion;
            B[x][y] = A[i][j];
        }

    for (int i = 0;i < ax;i++)
        for (int j = 0; j < ay; j++){
           QColor * chsv = new QColor();
           chsv->setHsvF(A[i][j],1,1);
           QColor*crgba = HSVtoRGB(chsv);
           Apic.setPixelColor(i,j,*crgba);
        }

    ui->ArrAView->setPixmap(QPixmap::fromImage(Apic).scaled(ui->ArrAView->width(),ui->ArrAView->height(),Qt::KeepAspectRatio));

    for (int i = 0;i < bx;i++)
        for (int j = 0; j < by; j++){
           QColor* chsv = new QColor();
           chsv->setHsvF(B[i][j],1,1);
           QColor*crgba = HSVtoRGB(chsv);
           Bpic.setPixelColor(i,j,*crgba);
        }
    ui->ArrBView->setPixmap(QPixmap::fromImage(Bpic).scaled(ui->ArrBView->width(),ui->ArrBView->height(),Qt::KeepAspectRatio));
}

QColor* Widget::HSVtoRGB(QColor* col){
   double r,g,b,a;
    double *h = 0, *s = 0,*v = 0,*a1 = 0;
    col->getHslF(h,s,v,a1);
    int Hi = (int)((240 + (*h * (180.0/Pi)))/60) % 6;
    double Vmin = ((1 - *s) * *v)/100;
    double alpha = ((int)((*v - Vmin)* (240 + (*h * (180.0/Pi)))) % 60)/60;
    double Vinc = Vmin + alpha;
    double Vdec = *v - alpha;
    if(Hi == 5)
    {r = Vinc; g = Vmin; b = *v; a = alpha;}
    else
    {r = *v; g = Vmin; b = Vdec; a = alpha;}
    QColor * res = new QColor();
    res->setRgbF(r,g,b,a);
    return res;
}

void Widget::resizeEvent(QResizeEvent * re){
   setImages();
}
