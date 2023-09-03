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
    //    //绘制字体
    //    QLabel *label = new QLabel("四川大学2023暑期实习：集群围捕无人机",this);
    //    label->setGeometry(-300,-300,400,400);  // Set geometry (position and size)
    //    label->setStyleSheet("background-color: black;");
    //    label->setAlignment(Qt::AlignCenter);//设置对齐方式
    //    QFont font("Arial", 20, QFont::Bold);//设置字体大小和样式
    //    label->setFont(font);
    //    label->setStyleSheet("color: blue;");
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
    pixfly[0].load(":/qss/fly1_1.png");
    pixfly[1].load(":/qss/fly2_1.png");
    pixfly[2].load(":/qss/fly3_1.png");
    pixcar[0].load(":/qss/car4_1.png");
    pixcar[1].load(":/qss/car5_1.png");
    pixbg.load(":/qss/hg.jpg");
    pixbg1.load(":/qss/OIP.jpg");
    title.load(":/qss/title.jpg");
    pic_bg.load(":/qss/bg3.png");

    int flywidth[3]={40,40,40};
    int flyheight[3]={40,40,40};

    for(int i=0; i<3; i++)
    {
        flywidth[i] = flywidth[i]/(1 + (float)idz[i]*0.6/200);
        flyheight[i] = flyheight[i]/(1 + (float)idz[i]*0.6/200);
        for(int j=i;j>0;j--)//高度排序
        {
            if(idz[horder[j]]<idz[horder[j-1]]){
                int temp=horder[j-1];
                horder[j-1]=horder[j];
                horder[j]=temp;
            }
        }
    }


    //painter.drawPixmap(0,0,this->width(),this->height(),pixbg1);
    painter.translate(this->width()/2, this->height()/2);//将（100，100）设为坐标原点
    //painter.drawPixmap(-170,-168,344,336,pixbg);
    painter.drawPixmap(-(this->width()/2),-(this->height()/2)+50,this->width(),this->height(),pic_bg);
    painter.drawPixmap(-(this->width()/2),-(this->height()/2),this->width(),180,title);
    //painter.drawPixmap(-(this->width()/2),-(this->height()/2)+200,this->width(),this->height()-200,pic_bg);
    painter.drawPixmap(-170,-168,344,336,pixbg);
    painter.drawRect(-170,-168,344,336);   // 绘制矩形框的位置和大小

    painter.translate(idx[3],idy[3]);
    painter.rotate(idw[3]); //旋转
    painter.drawPixmap(0,0,carsize[0],carsize[1],pixcar[0]);  //小车4
    painter.rotate(-idw[3]); //旋转
    painter.translate(-idx[3],-idy[3]);

    painter.translate(idx[4],idy[4]);
    painter.rotate(idw[4]); //旋转
    painter.drawPixmap(0,0,carsize[0],carsize[1],pixcar[1]);  //小车5
    painter.rotate(-idw[4]); //旋转
    painter.translate(-idx[4],-idy[4]);

    for(int i=0;i<3;i++)
    {
        if(idx[i]==0&&idy[i]==0&&idz[i]==0)
            continue;
        painter.translate(idx[horder[i]],idy[horder[i]]);
        painter.rotate(idw[horder[i]]); //旋转
        painter.drawPixmap(0,0,flywidth[horder[i]],flyheight[horder[i]],pixfly[horder[i]]);  //飞机
        painter.rotate(-idw[horder[i]]); //旋转
        painter.translate(-idx[horder[i]],-idy[horder[i]]);
    }



}

void paintarea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 获取鼠标点击的位置
        QPoint pos = event->pos();

        // 判断鼠标点击位置是否在绘图区域内
        QRect targetRect;//(100, 100, 200, 200); // 获取绘图区域
        targetRect = pixfly[0].rect();
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



