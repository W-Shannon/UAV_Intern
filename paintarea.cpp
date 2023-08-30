#include "paintarea.h"
#include "ui_paintarea.h"
#include "include.h"

paintarea::paintarea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paintarea)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, 800, 480);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);

    /* 定时器实例化 */
    timer = new QTimer(this);

    /* 定时100ms */
    timer->start(100);

    /* 信号槽连接 */
    //connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeOut()));
    connect(timer, &QTimer::timeout, this, &paintarea::timerTimeOut);
}

paintarea::~paintarea()
{
    delete ui;
}


QPoint readyapply,prereadyapply,afterapply=QPoint(0,0);

void paintarea::paintEvent(QPaintEvent *event)
{

    // 绘图
    QPainter painter(this);
    pixfly.load(":/qss/fly_ui.png");
    pixcar.load(":/qss/car.png");
    int width[3]={40,40,40};
    int height[3]={40,40,40};
    int horder[3]={1,2,3};

    for(int i=0; i<3; i++)
    {
        width[i] = width[i]/(1 + (float)idz[i]*0.5/200);
        height[i] = height[i]/(1 + (float)idz[i]*0.5/200);
//        for(int j=i;j>0;j--)//高度排序
//        {
//            if(idz[horder[j]]<idz[horder[j-1]]){
//                int temp=horder[j-1];
//                horder[j-1]=horder[j];
//                horder[j]=temp;
//            }
//        }
    }
    painter.translate(this->width()/2, this->height()/2);//将（100，100）设为坐标原点


    painter.translate(idx[3],idy[3]);
    painter.rotate(idw[3]); //旋转
    painter.drawPixmap(0,0,40,30,pixcar);  //小车4
    painter.rotate(-idw[3]); //旋转
    painter.translate(-idx[3],-idy[3]);

    painter.translate(idx[4],idy[4]);
    painter.rotate(idw[4]); //旋转
    painter.drawPixmap(0,0,40,30,pixcar);  //小车5
    painter.rotate(-idw[4]); //旋转
    painter.translate(-idx[4],-idy[4]);

    for(int i=0;i<3;i++)
    {
        painter.translate(idx[horder[i]],idy[horder[i]]);
        painter.rotate(idw[horder[i]]); //旋转
        painter.drawPixmap(0,0,width[horder[i]],height[horder[i]],pixfly);  //飞机
        painter.rotate(-idw[horder[i]]); //旋转
        painter.translate(-idx[horder[i]],-idy[horder[i]]);
    }
//    painter.translate(idx[1],idy[1]);
//    painter.rotate(idw[1]); //旋转
//    painter.drawPixmap(0,0,width[1],height[1],pixfly);  //飞机2
//    painter.rotate(-idw[1]); //旋转
//    painter.translate(-idx[1],-idy[1]);

//    painter.translate(idx[2],idy[2]);
//    painter.rotate(idw[2]); //旋转
//    painter.drawPixmap(0,0,width[2],height[2],pixfly);  //飞机3
//    painter.rotate(-idw[2]); //旋转
//    painter.translate(-idx[2],-idy[2]);

    //painter.translate(-100, -100);  //让图片的中心作为旋转的中心

//        // 实现图片的缩放
//        painter.translate(100,100); //将（100，100）设为坐标原点
//        qreal width = pix.width(); //获得以前图片的宽和高
//        qreal height = pix.height();

//        pix = pix.scaled(width*2,height*2,Qt::KeepAspectRatio);
//        //将图片的宽和高都扩大两倍，并且在给定的矩形内保持宽高的比值
//        painter.drawPixmap(100,100,pix);
//        painter.translate(-100, -100); //让图片的中心作为旋转的中心

//        // 实现图片的旋转
//        painter.translate(500, 400); //让图片的中心作为旋转的中心
//        painter.rotate(90); //顺时针旋转90度
//        painter.drawPixmap(0,0,100,100,pix);
//        painter.rotate(-90); //顺时针旋转90度
//        painter.translate(-500, -400); //让图片的中心作为旋转的中心


}

void paintarea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 获取鼠标点击的位置
        QPoint pos = event->pos();

        // 判断鼠标点击位置是否在绘图区域内
        QRect targetRect;//(100, 100, 200, 200); // 获取绘图区域
        targetRect = pixfly.rect();
        if (targetRect.contains(pos))
        {
            qDebug() << "鼠标点击在绘图区域内";
        }
        else
        {
            qDebug() << "鼠标点击在绘图区域外";
        }

    }

   QWidget::mousePressEvent(event); // 调用基类的鼠标按下事件
}

void paintarea::timerTimeOut()
{
    /* 需要更新界面，不设置不更新 */
    this->update();
}



