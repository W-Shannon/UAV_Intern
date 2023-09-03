#ifndef UDPPAINT_H
#define UDPPAINT_H

#include "udpstates.h"
#include "paintarea.h"
class UdpPaint: public QObject
{
    Q_OBJECT
public:
    UdpPaint();
    paintarea*   PaintArea = new paintarea();
    udphandle*   h_thread;
 public slots:
    void UdptoPaint()
    {
        for(int i=0;i<5;i++)
            this->PaintArea->idx[i]=-1*this->h_thread->idy[i]/10;
        for(int i=0;i<5;i++)
            this->PaintArea->idy[i]=-1*this->h_thread->idx[i]/10;
        for(int i=0;i<5;i++)
            this->PaintArea->idz[i]=this->h_thread->idz[i]/10;
        for(int i=0;i<5;i++)
            this->PaintArea->idw[i]=-this->h_thread->idw[i]/10-90;
    }
};

#endif // UDPPAINT_H
