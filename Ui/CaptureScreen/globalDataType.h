#ifndef GLOBALDATATYPE_H
#define GLOBALDATATYPE_H

//Capture state
enum shotState
{
    initShot  =0,    //no area is selected.
    beginShot =1,    //start select target area.
    finishShot=2,    //in selected state.
    beginMoveShot =3,//move the target area.
    beginControl  =4,//operate the adjust box.
    editShot      =5,//at edit state, can not move and adjust the target area.
    editBeginShot =6,//in adding some one draw type.
    editingShot   =7,//someone draw operation is doing
    editEndShot   =8 //finish once draw operation,but can be cancel.
};

enum drawItemType
{
    drawNone     = 0,//no draw operation.
    drawRectange = 1,//add rectange.
    drawEllipse  = 2,//add ellipse.
    drawRamLine  = 3,//add random line.
    drawArrow    = 4,//add line with arrow
    drawText     = 5 //add text
};

//Adjust box id
enum controlPointEnum
{
    moveControlnone = 0,//none

    moveControltl = 1,  //top left point
    moveControltr = 2,  //top right point
    moveControlbl = 3,  //bottom left point
    moveControlbr = 4,  //bottom right point
    moveControltc = 5,  //top center point
    moveControlbc = 6,  //bottom center point
    moveControllc = 7,  //left center point
    moveControlrc = 8   //right center point
};

//some default attribute
const qreal  defauleLineWidth=2;
const QColor defaultColor(0,0,0);
const QColor defaultBorderColor(0,160,255);
const QColor defaultShadowColor(0,0,0,96);
const QColor defaultDrawXYHWColor(239,234,228,200);//位置宽度提示信息框颜色
const qreal  defaultSpaceSize=2;
const QSize  defaultInputboxSize(90,30);
const int    defaultFontSize = 8;
const QFont  defaultFont("system",defaultFontSize);
//	QFont ( const QString & family, int pointSize = -1, int weight = -1, bool italic = false )

//tip information for user select area,position and size,etc
const int    infoTipWidth = 150;
const int    infoTipHeight= 60;
const int    infoWelcomeWidth = 300; //温馨提示框的宽度
const int    infoWelcomeHeight= 100; //温馨提示框的高度
const QColor infoWelcomeColor(100,100,100,200);
//const QString infoWelcome = QString(QObject::tr("Welcome You\nIDKin Screen Capture!"));

const QColor colorPalette[16]={QColor(0,0,0),
                               QColor(128,128,128),
                               QColor(128,0,0),
                               QColor(128,128,0),
                               QColor(0,128,0),
                               QColor(0,0,128),
                               QColor(128,0,128),
                               QColor(0,128,128),
                               QColor(255,255,255),
                               QColor(192,192,192),
                               QColor(255,0,0),
                               QColor(255,255,0),
                               QColor(0,255,0),
                               QColor(0,0,255),
                               QColor(255,0,255),
                               QColor(0,255,255)
                              };
#endif // GLOBALDATATYPE_H
