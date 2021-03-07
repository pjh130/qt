#ifndef CAPSELECTOR_H
#define CAPSELECTOR_H
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "globalDataType.h"
class CapSelector
{
public:
    CapSelector();
protected:
    QPoint posBegin;//Start select point
    QPoint posEnd;  //End select point
    QPoint posMoveBegin;//Start move point
    QPoint posMoveEnd;  //end move point

    //8 pick boxes
    QRect tlRect; //top left
    QRect trRect; //top right
    QRect blRect; //bottom left
    QRect brRect; //bottom right
    QRect tcRect; //top center
    QRect bcRect; //bottom center
    QRect lcRect; //left center
    QRect rcRect; //right center

    bool controlPoint8set;

public:
    void reset()
    {
        posBegin = QPoint();
        posEnd   = QPoint();
        posMoveBegin = QPoint();
        posMoveEnd   = QPoint();
        controlPoint8set = false;
        tlRect   = QRect();
        trRect   = QRect();
        blRect   = QRect();
        brRect   = QRect();
        tcRect   = QRect();
        bcRect   = QRect();
        lcRect   = QRect();
        rcRect   = QRect();
    }

    void setBeginPoint(QPoint pos)
    {
        posBegin = pos;
        posEnd = pos;
    }
    QPoint &getBeginPoint()
    {
        return posBegin;
    }

    void setEndPoint(QPoint pos)
    {
        posEnd = pos;
    }
    QPoint &getEndPoint()
    {
        return posEnd;
    }

    void setMoveBeginPoint(QPoint pos)
    {
        posMoveBegin = pos;
        posMoveEnd   = pos;
    }
    QPoint &getMoveBeginPoint()
    {
        return posMoveBegin;
    }

    void setMoveEndPoint(QPoint pos)
    {
        posMoveEnd = pos;
    }
    QPoint &getMoveEndPoint()
    {
        return posMoveEnd;
    }
    static QRect getRect(const QPoint begin,const QPoint end);
    QRect geometry()
    {
        return CapSelector::getRect(posBegin,posEnd);
    }
    void setGeometry(QRect rect)
    {
        posBegin = rect.topLeft();
        posEnd   = rect.bottomRight();
    }

    void MovedGeometry(QRect rcFrame);
    QRect getMoveControlSelectedRect(controlPointEnum ctrlPointID);
    void setControlPoint8(QRect rect);
    void drawControlPoint(QPainter *painter);
    bool inSelectRect(QPoint pos)
    {
        QRect rt = geometry();
        if(rt.contains(pos))
            return true;
        else
            return false;
    }
    controlPointEnum getMoveControlPointID(QPoint pos);
private:
    void checkMoveEndPoint(QRect rc);
    int getMinValue(int num1, int num2)
    {
      return num1<num2?num1:num2;
    }
};

#endif // CAPSELECTOR_H
