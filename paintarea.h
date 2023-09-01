#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

namespace Ui {
class paintarea;
}

class paintarea : public QWidget
{
    Q_OBJECT

public:
    explicit paintarea(QWidget *parent = nullptr);
    ~paintarea();
    void SetFly();
    void slotDisplayPlaneInfo(int row, int column);
    int idx[5];
    int idy[5];
    int idz[5];
    int idw[5];
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::paintarea *ui;
    QTimer *timer;      //定时器，用于定时更新界面
    QPixmap pixfly[3];
    QPixmap pixcar[2];
    QPixmap pixbg;
    int     rowbuff;
    int     colbuff;
    int       rowcolumn = -1;
    int horder[3]={0,1,2};
    int carsize[2]={48,36};

private slots:
    void timerTimeOut();



};

#endif // PAINTAREA_H
