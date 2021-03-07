#include "capselector.h"

CapSelector::CapSelector()
{
    reset();
}

QRect CapSelector::getRect(const QPoint begin,const QPoint end)
{
    int x,y,width,height;
    width = qAbs(begin.x() - end.x());
    height = qAbs(begin.y() - end.y());
    x = begin.x() < end.x() ? begin.x() : end.x();
    y = begin.y() < end.y() ? begin.y() : end.y();

    return QRect(x,y,width,height);
}

void CapSelector::setControlPoint8(QRect rect)
{
    int x,y;
    QPoint tlPoint = rect.topLeft(); //左上点
    QPoint trPoint = rect.topRight(); //右上点
    QPoint blPoint = rect.bottomLeft(); //左下点
    QPoint brPoint = rect.bottomRight(); //右下点

    x = (tlPoint.x()+trPoint.x())/2;
    y = tlPoint.y();
    QPoint tcPoint = QPoint(x,y);

    x = (blPoint.x()+brPoint.x())/2;
    y = blPoint.y();
    QPoint bcPoint = QPoint(x,y);

    x = tlPoint.x();
    y = (tlPoint.y()+blPoint.y())/2;
    QPoint lcPoint = QPoint(x,y);

    x = trPoint.x();
    y = (trPoint.y()+brPoint.y())/2;
    QPoint rcPoint = QPoint(x,y);

    tlRect = QRect(tlPoint.x()-3,tlPoint.y()-3,6,6); //左上点
    trRect = QRect(trPoint.x()-3,trPoint.y()-3,6,6); //右上点
    blRect = QRect(blPoint.x()-3,blPoint.y()-3,6,6); //左下点
    brRect = QRect(brPoint.x()-3,brPoint.y()-3,6,6); //右下点
    tcRect = QRect(tcPoint.x()-3,tcPoint.y()-3,6,6); //上中点
    bcRect = QRect(bcPoint.x()-3,bcPoint.y()-3,6,6); //下中点
    lcRect = QRect(lcPoint.x()-3,lcPoint.y()-3,6,6); //左中点
    rcRect = QRect(rcPoint.x()-3,rcPoint.y()-3,6,6); //右中点

    controlPoint8set = true;
}
void CapSelector::drawControlPoint(QPainter *painter)
{
    if(painter && controlPoint8set)
    {
        painter->fillRect(tlRect,defaultBorderColor);
        painter->fillRect(trRect,defaultBorderColor);
        painter->fillRect(blRect,defaultBorderColor);
        painter->fillRect(brRect,defaultBorderColor);
        painter->fillRect(tcRect,defaultBorderColor);
        painter->fillRect(bcRect,defaultBorderColor);
        painter->fillRect(lcRect,defaultBorderColor);
        painter->fillRect(rcRect,defaultBorderColor);
    }
}

controlPointEnum CapSelector::getMoveControlPointID(QPoint pos)
{
    controlPointEnum result = moveControlnone;

    if(tlRect.contains(pos)){
      result = moveControltl;
    }
    else if(tcRect.contains(pos)){
      result = moveControltc;
    }
    else if(trRect.contains(pos)){
      result = moveControltr;
    }
    else if(rcRect.contains(pos)){
      result = moveControlrc;
    }
    else if(brRect.contains(pos)){
      result = moveControlbr;
    }
    else if(bcRect.contains(pos)){
      result = moveControlbc;
    }
    else if(blRect.contains(pos)){
      result = moveControlbl;
    }
    else if(lcRect.contains(pos)){
      result = moveControllc;
    }
    else{
      result = moveControlnone;
    }

    return result;
}

void CapSelector::MovedGeometry(QRect rcFrame)
{
    int moveX,moveY;
    checkMoveEndPoint(rcFrame);//对移动选区进行判断，当移动的选区超出边界，则停止移动
    moveX = posMoveEnd.x() - posMoveBegin.x();
    moveY = posMoveEnd.y() - posMoveBegin.y();
    posBegin.setX(posBegin.x() + moveX);
    posBegin.setY(posBegin.y() + moveY);
    posEnd.setX(posEnd.x() + moveX);
    posEnd.setY(posEnd.y() + moveY);
    posMoveBegin = posMoveEnd;
}

void CapSelector::checkMoveEndPoint(QRect rc)
{
    int x,y;
    QRect selectedRect =geometry();
    QPoint bottomRightPoint = selectedRect.bottomRight();
    x = posMoveEnd.x() - posMoveBegin.x();
    y = posMoveEnd.y() - posMoveBegin.y();

    if(x + selectedRect.x() < rc.x()){ //当移动后X坐标小于零时，则出现选区丢失，则计算出moveEndPoint的X最大坐标值，进行赋值
      posMoveEnd.setX(qAbs(selectedRect.x()-posMoveBegin.x()));
    }

    if(y + selectedRect.y() < rc.y()){ //当移动后Y坐标小于零时，则出现选区丢失，则计算出moveEndPoint的Y最大坐标值，进行赋值
      posMoveEnd.setY(qAbs(selectedRect.y() - posMoveBegin.y()));
    }

    if(x + bottomRightPoint.x() > rc.width()){ //当移动选区后，出现超出整个屏幕的右面时，设置moveEndPoint的X的最大坐标
      posMoveEnd.setX(rc.width() - bottomRightPoint.x() + posMoveBegin.x());
    }

    if(y + bottomRightPoint.y() > rc.height()){ //当移动选区后，出现超出整个屏幕的下面时，设置moveEndPoint的Y的最大坐标值
      posMoveEnd.setY(rc.height() - bottomRightPoint.y() + posMoveBegin.y());
    }
}

QRect CapSelector::getMoveControlSelectedRect(controlPointEnum ctrlPointID)
{
    //use posMoveEnd modity topleft and bottom right
    switch(ctrlPointID)
    {
    case moveControltl:
        posBegin = posMoveEnd;
        break;
    case moveControltr:
        posBegin.setY(posMoveEnd.y());
        posEnd.setX(posMoveEnd.x());
        break;
    case moveControlbl:
        posBegin.setX(posMoveEnd.x());
        posEnd.setY(posMoveEnd.y());
        break;
    case moveControlbr:
        posEnd = posMoveEnd;
        break;
    case moveControltc:
        posBegin.setY(posMoveEnd.y());
        break;
    case moveControlbc:
        posEnd.setY(posMoveEnd.y());
        break;
    case moveControllc:
        posBegin.setX(posMoveEnd.x());
        break;
    case moveControlrc:
        posEnd.setX(posMoveEnd.x());
        break;
    default:
        break;
    }
    return geometry(); //获取选区
}
