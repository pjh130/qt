#ifndef CAPTUREWIDGET_H
#define CAPTUREWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QVector>
#include <QPainter>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QLineEdit>
//#include "qxtglobalshortcut/qxtglobalshortcut.h"
#include "capselector.h"
#include "globalDataType.h"
#include "recttoolbar.h"
#include "texttoolbar.h"
#include <QShortcut>
#include <QScreen>
//#include "CaptureScreenDll_global.h"

const QPen   defaultPen(defaultColor,defauleLineWidth,Qt::SolidLine,Qt::FlatCap);

enum MouseEventType   //mouse operation type
{
    PressEvent   = 0, //mouse button press
    MoveEvent    = 1, //mouse move
    ReleaseEvent = 2, //mouse button release
    DoubleClick  = 3  //mouse button double click
};

class CaptureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureWidget(QWidget *parent = 0);
    ~CaptureWidget();
public:
    bool setHotKey(QString key); //set hot key for modify
    void startCapture();
public:
    static QWidget* _Creator(QWidget *parent=0);
private slots:
    void toggle();
signals:
    void exitCapture(const QPixmap &finishPixmap);
//    void finishPixmap(const QPixmap &finishPixmap);
protected:
    //mouse events handler
    virtual void mousePressEvent(QMouseEvent *evt);
    virtual void mouseReleaseEvent(QMouseEvent *evt);
    virtual void mouseMoveEvent(QMouseEvent *evt);
    virtual void mouseDoubleClickEvent(QMouseEvent *evt);
    //Capture operation function,all states
    bool MouseEvents(QMouseEvent *evt,MouseEventType MouseOperation);

    //key events handler
    virtual void keyPressEvent ( QKeyEvent * event );

    //widget fresh handler
    virtual void paintEvent(QPaintEvent * event);
private:
//    QxtGlobalShortcut *globalShortCut;

    QPixmap bmpCapture;                //image is selected by user
    QPixmap bmpDeskCapture;            //whole image when start capture screen saved.
    QRect   rtDeskCapture;             //desktop geometry
    QRect   rtPickRect;                //the selected area position and size
    QSize   infoTipSize;               //tip information for user select area,position and size,etc
    CapSelector      selectorBoxes;    //the area is selected by user.
    shotState        currentShotState; //当前的截屏状态

    drawItemType     drawGeoType;      //current draw operation type
    QPen             linePen;          //pen used by draw line
    QFont            textFont;

    controlPointEnum controlValue;     //记录移动控制点的值
    bool             drawOnce;         //once draw operation finish flag.
    QPoint           drawFrom;         //draw operation start point,for rectange,ellipse
    QPoint           drawTo;           //draw operation end point,for rectange,ellipse
    QVector<QPoint>  drawRandomLines;  //draw random line operate points.

    QToolBar *mainToolbar;             //main tool bar.
    QActionGroup *actDraws;            //all draw operation in one group because only one draw type in working,
    QAction *actDrawRect;             //draw rectange starting or ending operation.
    QAction *actDrawEllipse;          //draw ellipse starting or ending operation.
    QAction *actDrawRandomLine;       //draw random line starting or ending operation.
    QAction *actDrawArrow;            //add arrow operation.
    QAction *actDrawText;             //add text operation.
    QAction *actCopyToClipBox;        //copy target image to clip box.
    QAction *actSaveToFile;           //save target image to file.
    QAction *actQuit;                 //quit capture lost the capture image.

    QLineEdit *textInputBox;           //Text input box
    QRect      rtTextInputAdjustBox[4];//for adjust the text input box position and size.
    QRect      rtTextInput;            //input box rectange.
    QString    textInputString;        //input box content.

    RectToolBar *attrLineSettingBar;
    TextToolBar *attrTextSettingBar;

    QColor     lineColorUsed;              //attribute draw rectange ellipse,etc color
    QColor     textColorUsed;              //attribute draw rectange ellipse,etc color
    QCursor    colorCursor;                //defaultCursor
protected slots:
    void attrTextChanged();
    void attrLineChanged();
protected slots:
    void drawRectAct();
    void drawEllipseAct();
    void drawRamLineAct();
    void drawArrowAct();
    void drawTextAct();
    void copyToClipboxAct();
    void saveToFileAct();
    void quitAct();

    void inputBoxChanged(QString strContent);

private:
    void resetPickStatus();
    void resetDrawStatusValues();
    void updateMouseShape(controlPointEnum emPickerID);
    void createActions();
    void createToolBar();
    void addActionsToToolBar();
    QPoint adjustPointIntoRect(QPoint pos,QRect rc);
    void showToolbars(QRect rectFrame);
    void showWelComeTips(QPainter *painter);

    void ShowAttrExtToolBar(QRect rectFrame,QWidget* attrBar);

    QPoint showInputBox(QRect rectFrame,QPoint pos);
    void resetTextInput();

    void drawXYWHInfo(QPainter *painter);
    void drawGeometry(QPainter *painter,bool isWidgetPainter = false,bool isSave=false);
    void setTextinputControlPoint(QRect rc);
    void drawToTargetPixmap();
protected:
    bool initShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool beginShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool finishShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool beginMoveShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool beginControlHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool editShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool editBeginShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool editingShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
    bool editEndShotHandler(QMouseEvent *evt,MouseEventType MouseOperation);
};

#endif // CAPTUREWIDGET_H
