#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#include "capturewidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>
#include <QClipboard>
#include <QTextCodec>
#include <QFileDialog>
#include <QCursor>
#include <QTranslator>
#include <QLocale>
#include "globalDataType.h"
#include <qmath.h>
#include <QDebug>

QTranslator *g_translator = new QTranslator();

CaptureWidget::CaptureWidget(QWidget *parent) :
    QWidget(NULL,Qt::CustomizeWindowHint|Qt::FramelessWindowHint/*|Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint*/)
{


    /************************************************************
     * Application code page config
     *
     * Description:
     * 1. Change system default code page (cp936)  to UTF-8
     * 2. Add translator
     * 3. Default translator is en_US
     ************************************************************/
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("GBK");
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    //Load default language
    g_translator = new QTranslator();
    if(!g_translator) {
        qWarning("ERROR: Load Translator Failure.");
    }
    //读取配置文件中的语言配置
    //do....

    //如果没有配置, 则自动适配
    QString locale = QLocale::system().name();
    if("zh_CN" == locale || "zh_TW" == locale || "en_US" == locale){
        g_translator->load(QString("intl\\captureScreen.") + locale);
    }else{
        g_translator->load(QString("intl\\captureScreen.") + "en_US");
    }
    qApp->installTranslator(g_translator);

//    setAttribute(Qt::WA_DeleteOnClose);
    setWindowState(Qt::WindowFullScreen);//setGeometry(QApplication::desktop()->geometry());
    infoTipSize = QSize(infoTipWidth,infoTipHeight);

    colorCursor = QCursor(QPixmap(":/cursor.png"));

    drawGeoType = drawNone;
//        QTextCodec *zhCodec = QTextCodec::codecForLocale();
    //    QTextCodec::setCodecForTr(zhCodec);
    //register HotKey default hot kye is "Ctrl+Alt+A"
    //    globalShortCut = new QxtGlobalShortcut(QKeySequence("Ctrl+Alt+A"), this);

    createActions();
    createToolBar();
    addActionsToToolBar();

    textInputBox = new QLineEdit(this);
    textInputBox->setStyleSheet(QString::fromUtf8("border:2px dotted #888;"));
    linePen     = defaultPen;
    textFont    = this->font();//defaultFont;
    lineColorUsed=defaultColor;
    textColorUsed=defaultColor;

    //connect actions to handler
    connect(actDrawRect,SIGNAL(triggered()),this,SLOT(drawRectAct()));
    connect(actDrawEllipse,SIGNAL(triggered()),this,SLOT(drawEllipseAct()));
    connect(actDrawRandomLine,SIGNAL(triggered()),this,SLOT(drawRamLineAct()));
    connect(actDrawArrow,SIGNAL(triggered()),this,SLOT(drawArrowAct()));
    connect(actDrawText,SIGNAL(triggered()),this,SLOT(drawTextAct()));
    connect(actCopyToClipBox,SIGNAL(triggered()),this,SLOT(copyToClipboxAct()));
    connect(actSaveToFile,SIGNAL(triggered()),this,SLOT(saveToFileAct()));
    connect(actQuit,SIGNAL(triggered()),SLOT(quitAct()));

    connect(textInputBox,SIGNAL(textChanged(QString)),this,SLOT(inputBoxChanged(QString)));

    connect(attrTextSettingBar,SIGNAL(attrChanged()),this,SLOT(attrTextChanged()));
    connect(attrLineSettingBar,SIGNAL(attrChanged()),this,SLOT(attrLineChanged()));
    //set tool bar's attribute
    mainToolbar->setAutoFillBackground(true);
    mainToolbar->setFloatable(true);
    mainToolbar->setMovable(false);
    mainToolbar->setVisible(false);

    textInputBox->setAutoFillBackground(true);
    textInputBox->setVisible(false);

    //    connect(globalShortCut, SIGNAL(activated()),this, SLOT(toggle()));//handler for HotKey

    resetPickStatus();
    resetTextInput();
    selectorBoxes.reset();
    setVisible(false);
    setMouseTracking(true);
}

CaptureWidget::~CaptureWidget()
{
    selectorBoxes.reset();
    //    if(NULL != globalShortCut)
    //    {
    //        delete globalShortCut;
    //        globalShortCut = NULL;
    //    }
}

void CaptureWidget::inputBoxChanged(QString strContent)
{
    textInputString = strContent;
}

//for change HotKey
bool CaptureWidget::setHotKey(QString key)
{
    //程序内的热键
    QShortcut *shortcut = new QShortcut(QKeySequence(key),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(toggle()));
    return true;

    //hot key is initialized.
    //    if(globalShortCut)
    //    {
    //        globalShortCut->setShortcut(QKeySequence(key));
    //        return true;
    //    }
    //    //hot key is not initialized.
    //    else
    //    {
    //        globalShortCut = new QxtGlobalShortcut(QKeySequence("Ctrl+Alt+F12"), this);
    //        connect(globalShortCut, SIGNAL(activated()),this, SLOT(toggle()));//handler for HotKey
    //    }
    return false;
}

//Initialize the text input state.
void CaptureWidget::resetTextInput()
{
    textInputBox->setVisible(false);
    textInputBox->clearFocus();
    textInputBox->clear();
    rtTextInput  = QRect();
    rtTextInputAdjustBox[0]= QRect();
    rtTextInputAdjustBox[1]= QRect();
    rtTextInputAdjustBox[2]= QRect();
    rtTextInputAdjustBox[3]= QRect();
}

void CaptureWidget::setTextinputControlPoint(QRect rc)
{
    QPoint tlPoint = rc.topLeft(); //左上点
    QPoint trPoint = rc.topRight(); //右上点
    QPoint blPoint = rc.bottomLeft(); //左下点
    QPoint brPoint = rc.bottomRight(); //右下点
    rtTextInputAdjustBox[0] = QRect(tlPoint.x()-2,tlPoint.y()-2,6,6); //左上点
    rtTextInputAdjustBox[1] = QRect(trPoint.x()-2,trPoint.y()-2,6,6); //右上点
    rtTextInputAdjustBox[2] = QRect(blPoint.x()-2,blPoint.y()-2,6,6); //左下点
    rtTextInputAdjustBox[3] = QRect(brPoint.x()-2,brPoint.y()-2,6,6); //右下点
}

//clear all state.
void CaptureWidget::resetPickStatus()
{
    currentShotState = initShot;
    controlValue     = moveControlnone;
    rtPickRect       = QRect();
    bmpCapture       = QPixmap();

    switch(drawGeoType)
    {
    case drawRectange:
        actDrawRect->setChecked(false);
        break;
    case drawEllipse:
        actDrawEllipse->setChecked(false);
        break;
    case drawRamLine:
        actDrawRandomLine->setChecked(false);
        break;
    case drawArrow:
        actDrawArrow->setChecked(false);
        break;
    case drawText:
        actDrawText->setChecked(false);
        resetTextInput();
        break;
    default:
        break;
    }
    drawGeoType = drawNone;
    drawOnce    = false;
    //    linePen     = defaultPen;
    mainToolbar->setVisible(false);
    attrLineSettingBar->setVisible(false);
    attrTextSettingBar->setVisible(false);

    setCursor(colorCursor);
    //setCursor(Qt::ArrowCursor);
}

void CaptureWidget::resetDrawStatusValues()
{
    drawOnce = false;
    drawFrom = drawTo = QPoint(0,0);
    drawRandomLines.clear();
    textInputBox->clear();
    textInputString.clear();
}

void CaptureWidget::paintEvent(QPaintEvent * event)
{
    QColor shadowColor = defaultShadowColor;//阴影颜色设置
    QPainter painter;

    painter.begin(this);

    //draw the background
    if(rtDeskCapture.width()>0 && rtDeskCapture.height()>0)
    {
        painter.drawPixmap(0,0,rtDeskCapture.width(),rtDeskCapture.height(),bmpDeskCapture);
        painter.fillRect(0,0,rtDeskCapture.width(),rtDeskCapture.height(),shadowColor); //画影罩效果
    }
    if(currentShotState==initShot)
    {
        //showWelComeTips(&painter);
    }
    //Display the selected Pixmap and picker boxes
    if(rtPickRect.width()>0 && rtPickRect.height()>0)
    {
        painter.drawPixmap(rtPickRect,bmpCapture);
        selectorBoxes.setControlPoint8(rtPickRect);
        if(currentShotState==finishShot)
        {
            selectorBoxes.drawControlPoint(&painter);
            drawXYWHInfo(&painter);
        }
        else if(currentShotState == editShot)
        {
            //geometries have been serialized into bmpCapture
            if(drawOnce)
            {
                drawGeometry(&painter,true);
            }
        }
        else if(currentShotState==editBeginShot)
        {
            //in this state ,the geometries have been rendered into paint device.
            if(drawOnce)
            {
                drawGeometry(&painter,true);
            }
        }
        else if(currentShotState==editEndShot)
        {
            if(drawOnce)
            {
                drawGeometry(&painter,true);
            }
        }
    }
    painter.end();
    event->ignore();
}

void CaptureWidget::drawGeometry(QPainter *painter,bool isWidgetPainter,bool isSave)
{
    isSave = isSave;
    isWidgetPainter=isWidgetPainter;
    if(drawGeoType==drawRectange)
    {
        QRect rtDraw(drawFrom,drawTo);
        //        if(isSave)
        //            linePen = QPen(attrLineSettingBar->getColor(),attrLineSettingBar->getLineWidth(),Qt::SolidLine,Qt::FlatCap);
        painter->save();
        painter->setPen(linePen);
        painter->drawRect(rtDraw);
        painter->restore();
        //        if(!isSave)
        //            linePen = QPen(attrLineSettingBar->getColor(),attrLineSettingBar->getLineWidth(),Qt::SolidLine,Qt::FlatCap);
    }
    else if(drawGeoType==drawEllipse)
    {
        QRect rtDraw(drawFrom,drawTo);
        //        if(isSave)
        //            linePen = QPen(attrLineSettingBar->getColor(),attrLineSettingBar->getLineWidth(),Qt::SolidLine,Qt::FlatCap);
        painter->save();
        painter->setPen(linePen);
        painter->drawEllipse(rtDraw.center(),rtDraw.width()/2,rtDraw.height()/2);
        painter->restore();
        //        if(!isSave)
        //            linePen = QPen(attrLineSettingBar->getColor(),attrLineSettingBar->getLineWidth(),Qt::SolidLine,Qt::FlatCap);
    }
    else if(drawGeoType==drawRamLine)
    {
        //        if(isSave)
        //            linePen = QPen(attrLineSettingBar->getColor(),attrLineSettingBar->getLineWidth(),Qt::SolidLine,Qt::FlatCap);
        painter->save();
        painter->setPen(linePen);
        painter->drawLines(drawRandomLines);
        painter->restore();
        //        if(!isSave)
        //            linePen = QPen(attrLineSettingBar->getColor(),attrLineSettingBar->getLineWidth(),Qt::SolidLine,Qt::FlatCap);
    }
    else if(drawGeoType==drawArrow)
    {
        painter->setRenderHint(QPainter::Antialiasing);

        bool isRight = true;
        qreal rotateAngle = 0;
        qreal lineLen = 0;

        //calculate arrow.
        if(drawFrom.x()==drawTo.x() && drawFrom.y()==drawTo.y())
        {
            //from point and to point is same,do nothing
            isRight = false;
        }
        else if(drawFrom.x()==drawTo.x())
        {
            if(drawFrom.y() < drawTo.y()) //down arrow
            {
                rotateAngle = M_PI*0.5;//rotate 90 degree
            }
            else                          //up arrow
            {
                rotateAngle =-M_PI*0.5;//rotate -90 degree
            }
            lineLen = qAbs(drawFrom.y() - drawTo.y());
        }
        else if(drawFrom.y()==drawTo.y())
        {
            if(drawFrom.x()>drawTo.x())  //left arrow
            {
                rotateAngle = M_PI;//rotate 180 degree
            }
            else                         //right arrow
            {
                rotateAngle = 0;//rotate 0 degree
            }
            lineLen = qAbs(drawFrom.x()-drawTo.x());
        }
        else
        {
            qreal absAngle = qAtan2(qAbs(drawTo.y()-drawFrom.y()),qAbs(drawTo.x()-drawFrom.x()));
            lineLen = qAbs(drawFrom.x() - drawTo.x()) /qCos(absAngle);
            if(drawFrom.x() < drawTo.x())//coordinate 1,4
            {
                if(drawFrom.y()<drawTo.y())   //coordiante 1
                {
                    rotateAngle = absAngle;//rotate -a degree
                }
                else                          //coordinate 1
                {
                    rotateAngle = -1.0 * absAngle;//rotate a degree
                }
            }
            else if(drawFrom.x()>drawTo.x())  //coordiante 2,3
            {
                if(drawFrom.y()<drawTo.y())   //coodinatte 2
                {
                    rotateAngle =  M_PI-absAngle;//rotate a degree;
                }
                else                          //coordinate 3
                {
                    rotateAngle =  M_PI+absAngle;//rotate -a degree;
                }
            }
        }
        if(isRight)  //need draw line with arrow
        {
            painter->setPen(linePen);
            rotateAngle = 180.0 *rotateAngle / M_PI;

            painter->save();
            painter->translate(drawFrom);
            painter->rotate(rotateAngle);
            painter->drawLine(QPoint(0,0),         QPoint(lineLen,0));
            painter->drawLine(QPoint(lineLen-8,-6),QPoint(lineLen,0));
            painter->drawLine(QPoint(lineLen-8,+6),QPoint(lineLen,0));
            painter->restore();
        }
    }
    else if(drawGeoType==drawText)
    {
        //        if(textInputBox->isVisible())
        //        {
        //            QColor fillCorlor(0,0,255);
        //            painter->drawRect(textInputBox->geometry());
        //            int i = 0;
        //            for(i = 0; i<4; i++)
        //            {
        //                painter->fillRect(rtTextInputAdjustBox[i],fillCorlor);
        //            }
        //        }

        QFont orgFont = painter->font();
        painter->setFont(textFont);
        painter->setPen(textColorUsed);
        painter->drawText(rtTextInput,textInputString,QTextOption(Qt::AlignVCenter));
        painter->setFont(orgFont);

        //        if(isSave)
        //            textFont = QFont("system",attrTextSettingBar->getFontSize());
        //        painter->save();
        //        painter->setPen(linePen);
        //        painter->drawLines(drawRandomLines);
        //        painter->restore();
        //        if(!isSave)
        //            textFont = QFont("system",attrTextSettingBar->getFontSize());
    }
}

//display information(position and size) tips for current selected window
void CaptureWidget::drawXYWHInfo(QPainter *painter)
{
    int x,y;
    QColor color = defaultDrawXYHWColor;
    QRect rect;
    QString strTipsText;
    switch(currentShotState)
    {
    case beginShot:
    case finishShot:
    case beginMoveShot:
    case beginControl:
        //        x = rtPickRect.topLeft().x();
        //        y = rtPickRect.y() > infoHeight ? rtPickRect.y()-infoHeight:rtPickRect.y();
        //        rect = QRect(x,y,infoWidth,infoHeight);
        x = rtPickRect.topLeft().x();
        y = rtPickRect.y() > infoTipSize.height() ? (rtPickRect.y()-infoTipSize.height()):rtPickRect.y();
        rect = QRect(QPoint(x,y),infoTipSize);
        strTipsText = QString(tr("Capture Info:\n X:%1 Y:%2\n W:%3 H:%4")).arg(rtPickRect.x(),4).arg(rtPickRect.y(),4)
                .arg(rtPickRect.width(),4).arg(rtPickRect.height(),4);
        painter->fillRect(rect,color);

        {
            QPen p(Qt::black);//设置画笔的颜色为黑色
            painter->setPen(p);
            painter->drawText(rect,Qt::AlignLeft|Qt::AlignVCenter,strTipsText);
        }
        break;
    default:
        break;
    }
}

//adjust the toolbar arrow,size and position ,then display the toolbar
/*void CaptureWidget::showToolbars(QRect rectFrame)
{
    QSize sizeToolBar = mainToolbar->size();
    QRect rcWidget  = geometry();
    QPoint realPoint = rectFrame.bottomLeft();
    mainToolbar->setOrientation(Qt::Horizontal);
    mainToolbar->adjustSize();
    sizeToolBar = mainToolbar->size();

    //default :工具栏显示在窗口下边

     //下边空余区域太小,将窗口显示到左边或右边
    if(rcWidget.bottomLeft().y()<(rectFrame.bottomLeft().y()+sizeToolBar.height() + defaultSpaceSize))
    {
        //纵向工具栏
        mainToolbar->setOrientation(Qt::Vertical);
        mainToolbar->adjustSize();
        sizeToolBar = mainToolbar->size();

        if((rectFrame.topLeft().x()-rcWidget.x())<(sizeToolBar.width() + defaultSpaceSize))//左边太小
        {
            if((rectFrame.topRight().x()+sizeToolBar.width() + defaultSpaceSize)>rcWidget.topRight().x())
            {
                //右边也不合适//最后只能显示在上边
                mainToolbar->setOrientation(Qt::Horizontal);
                mainToolbar->adjustSize();
                sizeToolBar = mainToolbar->size();
                realPoint.setX(rectFrame.x());
                realPoint.setY(rectFrame.y()-sizeToolBar.height()-defaultSpaceSize);
            }
            else   //右边
            {
                realPoint.setX(rectFrame.topRight().x()+defaultSpaceSize);
                realPoint.setY(rectFrame.topRight().y());
            }
        }
        else //左边
        {
            realPoint.setX(rectFrame.x()-sizeToolBar.width()-defaultSpaceSize);
            realPoint.setY(rectFrame.topLeft().y());
        }
    }
    else //下边
    {
        realPoint.setX(rectFrame.bottomLeft().x());
        realPoint.setY(rectFrame.bottomLeft().y()+defaultSpaceSize);
    }

    //set main toolbar position and display
    mainToolbar->move(realPoint);
    mainToolbar->setVisible(true);
}
*/
void CaptureWidget::showWelComeTips(QPainter *painter)
{
    //    if((welcomeTipPosition.x()+infoWelcomeWidth) > rtDeskCapture.bottomRight().x())
    //    {
    //        welcomeTipPosition.setX(rtDeskCapture.bottomRight().x()-infoWelcomeWidth);
    //    }
    //    if((welcomeTipPosition.y()+infoWelcomeHeight) > rtDeskCapture.bottomRight().y())
    //    {
    //        welcomeTipPosition.setY(rtDeskCapture.bottomRight().y()-infoWelcomeHeight);
    //    }
    //    QRect rect = QRect(welcomeTipPosition,QSize(infoWelcomeWidth,infoWelcomeHeight));

    //    QString strTipsText = QString(tr("温馨提示\n鼠标拖动进行截屏;截屏区域内右键保存;\n截屏区域外右键取消;ESC退出;"));

    QString infoWelcome = tr("Welcome You\n Screen Capture!");
    int x = (rtDeskCapture.width() - infoWelcomeWidth)/2;
    int y = (rtDeskCapture.height() - infoWelcomeHeight)/2;
    QRect rect = QRect(QPoint(x,y),QSize(infoWelcomeWidth,infoWelcomeHeight));

    painter->fillRect(rect,infoWelcomeColor);
    painter->setPen(QPen(Qt::white));//设置画笔的颜色为白色
    painter->drawText(rect,Qt::AlignCenter,infoWelcome);
}

QPoint CaptureWidget::showInputBox(QRect rectFrame,QPoint pos)
{
    QPoint posAdjust = pos;
    if(!textInputBox->isVisible() && rectFrame.contains(posAdjust))//point in frame rectange
    {
        textInputBox->resize(defaultInputboxSize);

        if(rectFrame.bottomRight().x()<(posAdjust.x()+defaultInputboxSize.width()))
        {
            pos.setX(rectFrame.bottomRight().x()-defaultInputboxSize.width());
        }
        if(rectFrame.bottomRight().y() < (posAdjust.y()+defaultInputboxSize.height()) )
        {
            pos.setY(rectFrame.bottomRight().y()-defaultInputboxSize.height());
        }
        textInputBox->move(posAdjust);
        textInputBox->clear();

        rtTextInput = textInputBox->geometry();
        setTextinputControlPoint(rtTextInput);

        textInputBox->setFont(defaultFont);
        textInputBox->setVisible(true);
        textInputBox->setFocus();
    }
    return posAdjust;
}

void CaptureWidget::mousePressEvent(QMouseEvent *evt)
{
    if(!MouseEvents(evt,PressEvent))
        QWidget::mousePressEvent(evt);
    else
        update();
}

void CaptureWidget::mouseMoveEvent(QMouseEvent *evt)
{
    if(!MouseEvents(evt,MoveEvent))
        QWidget::mouseMoveEvent(evt);
    else
        update();
}

void CaptureWidget::mouseReleaseEvent(QMouseEvent *evt)
{
    if(!MouseEvents(evt,ReleaseEvent))
        QWidget::mouseReleaseEvent(evt);
    else
        update();
}

void CaptureWidget::mouseDoubleClickEvent(QMouseEvent *evt)
{
    if(!MouseEvents(evt,DoubleClick))
        QWidget::mouseReleaseEvent(evt);
    else
        update();
}

bool CaptureWidget::MouseEvents(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;
    switch(currentShotState)
    {
    case initShot:
        bProcessed = initShotHandler(evt,MouseOperation);
        break;
    case beginShot:
        bProcessed = beginShotHandler(evt,MouseOperation);
        break;
    case finishShot:
        if((evt->buttons() & Qt::LeftButton) && (MouseOperation == DoubleClick))  //copy target image to clip box
        {
            if(rtPickRect.contains(evt->pos()))
                copyToClipboxAct();
        }
        else
        {
            bProcessed = finishShotHandler(evt,MouseOperation);
        }
        break;
    case beginMoveShot:
        bProcessed = beginMoveShotHandler(evt,MouseOperation);
        break;
    case beginControl:
        bProcessed = beginControlHandler(evt,MouseOperation);
        break;
    case editShot:
        if(evt->button() == Qt::LeftButton && MouseOperation == DoubleClick)
        {
            if(rtPickRect.contains(evt->pos()))
                copyToClipboxAct();
        }
        else
        {
            bProcessed = editShotHandler(evt,MouseOperation);
        }
        break;
    case editBeginShot:
        bProcessed = editBeginShotHandler(evt,MouseOperation);
        break;
    case editingShot:
        bProcessed = editingShotHandler(evt,MouseOperation);
        break;
    case editEndShot:
        bProcessed = editEndShotHandler(evt,MouseOperation);
        break;
    default:
        break;
    }
    if(MouseOperation == MoveEvent)    //modify cursor
    {
        if(currentShotState==initShot)
        {
            setCursor(colorCursor);
            //setCursor(Qt::ArrowCursor);
        }
        //modify the cursor when we move the select rectange
        else if(currentShotState==beginMoveShot)
        {
            setCursor(Qt::ClosedHandCursor);
        }
        //modify the cursor when the adjusting picker boxes
        else if(currentShotState == beginControl)
        {
            updateMouseShape(selectorBoxes.getMoveControlPointID(evt->pos()));
        }
        else if(currentShotState==finishShot)
        {
            //in rectange or in picker boxes
            if(selectorBoxes.inSelectRect(evt->pos()) ||
                    selectorBoxes.getMoveControlPointID(evt->pos())!=moveControlnone)
            {
                updateMouseShape(selectorBoxes.getMoveControlPointID(evt->pos()));
            }
            else // not in select rectange
            {
                setCursor(colorCursor);
                //                setCursor(Qt::ArrowCursor);
            }
        }
        else if(currentShotState==editShot || currentShotState==editBeginShot)
        {
            if(this->drawGeoType!=drawNone)
                setCursor(Qt::CrossCursor);
            else
                setCursor(colorCursor);
            //                setCursor(Qt::ArrowCursor);
        }
    }
    return bProcessed;
}

//in the edit state,can not draw at out of the selected rectange
QPoint CaptureWidget::adjustPointIntoRect(QPoint pos,QRect rc)
{
    QPoint curPosition = pos;
    if(curPosition.x()<rc.topLeft().x())
    {
        curPosition.setX(rc.topLeft().x());
    }
    else if(curPosition.x()>rc.bottomRight().x())
    {
        curPosition.setX(rc.bottomRight().x());
    }
    if(curPosition.y()<rc.topLeft().y())
    {
        curPosition.setY(rc.topLeft().y());
    }
    else if(curPosition.y()>rc.bottomRight().y())
    {
        curPosition.setY(rc.bottomRight().y());
    }
    return curPosition;
}

//modity cursor when the cursor pos in picker boxes
void CaptureWidget::updateMouseShape(controlPointEnum emPickerID)
{
    switch(emPickerID)
    {
    case moveControltl:
    case moveControlbr:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case moveControlbl:
    case moveControltr:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case moveControltc:
    case moveControlbc:
        setCursor(Qt::SizeVerCursor);
        break;
    case moveControllc:
    case moveControlrc:
        setCursor(Qt::SizeHorCursor);
        break;
    case moveControlnone:
    default:
        setCursor(Qt::OpenHandCursor);
        break;
    }
}

void CaptureWidget::startCapture()
{
    toggle();
}

void CaptureWidget::toggle()
{
    setCursor(colorCursor);

    //start capture screen
    if(!isVisible())
    {
        rtDeskCapture  = QApplication::desktop()->rect();
//        rtDeskCapture  = QApplication::desktop()->screenGeometry();
//        bmpDeskCapture = QPixmap::grabWindow(QApplication::desktop()->winId());

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    bmpDeskCapture = QPixmap::grabWindow(QApplication::desktop()->winId());
#else
    QScreen *pscreen = QApplication::primaryScreen();
    bmpDeskCapture = pscreen->grabWindow(QApplication::desktop()->winId());
#endif
        setVisible(true);
        setWindowState(windowState()|Qt::WindowFullScreen|Qt::WindowActive);
    }
    //touch the hot key when the capture screen in work,close it and lose all image and state.
    else
    {
        quitAct();
    }
}

void CaptureWidget::keyPressEvent ( QKeyEvent * event )
{
    //press esc key ont keyboard, will quit process, as asistant.
    Qt::KeyboardModifiers keyboardModf = QApplication::keyboardModifiers ();
    if(Qt::Key_Escape==event->key())
    {
        quitAct();
        qApp->quit();
    }
    else if(Qt::Key_Z==event->key()&&keyboardModf.testFlag(Qt::ControlModifier))
    {
        qDebug("currentShotState:%d\n",currentShotState);
        if(currentShotState==editEndShot)
        {
            resetDrawStatusValues();
            currentShotState = editShot;
            update();
        }
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void CaptureWidget::createToolBar()
{
    mainToolbar    =new QToolBar(tr("main tool bar"),this);
    attrLineSettingBar = new RectToolBar(this);
    attrTextSettingBar = new TextToolBar(this);
}

//init toolbar's actions
void CaptureWidget::createActions()
{
    actDraws         =new QActionGroup(this);

    actDrawRect      =new QAction(tr("Rectange"),this);
    actDrawRect->setIcon(QIcon(QString::fromUtf8(":/Rectange.png")));

    actDrawEllipse   =new QAction(tr("Ellipse"),this);
    actDrawEllipse->setIcon(QIcon(QString::fromUtf8(":/Ellipse.png")));

    actDrawRandomLine=new QAction(tr("Brush"),this);
    actDrawRandomLine->setIcon(QIcon(QString::fromUtf8(":/Brush01.png")));

    actDrawArrow     =new QAction(tr("Arrow"),this);
    actDrawArrow->setIcon(QIcon(QString::fromUtf8(":/Arrow.png")));

    actDrawText      =new QAction(tr("T"),this);
    actDrawText->setIcon(QIcon(QString::fromUtf8(":/Text.png")));

    actSaveToFile    =new QAction(tr("Save"),this);
    actSaveToFile->setIcon(QIcon(QString::fromUtf8(":/Save.png")));

    actCopyToClipBox =new QAction(tr("Copy"),this);
    actCopyToClipBox->setIcon(QIcon(QString::fromUtf8(":/Copy.png")));

    actQuit          =new QAction(tr("Quit"),this);
    actQuit->setIcon(QIcon(QString::fromUtf8(":/Quit.png")));

    //set draw actions
    actDraws->addAction(actDrawRect);
    actDraws->addAction(actDrawEllipse);
    actDraws->addAction(actDrawRandomLine);
    actDraws->addAction(actDrawArrow);
    actDraws->addAction(actDrawText);

    actDrawRect->setCheckable(true);
    actDrawEllipse->setCheckable(true);
    actDrawRandomLine->setCheckable(true);
    actDrawArrow->setCheckable(true);
    actDrawText->setCheckable(true);
}

//add actions into main tool bar
void CaptureWidget::addActionsToToolBar()
{
    //    actDraws->setExclusive(true);

    mainToolbar->setIconSize (QSize(24,24));
    //set control actions
    mainToolbar->addActions(actDraws->actions());
    mainToolbar->addAction(actCopyToClipBox);
    mainToolbar->addAction(actSaveToFile);
    mainToolbar->addAction(actQuit);
}

void CaptureWidget::drawRectAct(/*bool bToggled*/)
{
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }
    drawToTargetPixmap();
    //not in draw rectange state, goto rectange state
    if(drawGeoType!=drawRectange)
    {
        drawGeoType=drawRectange;
        actDrawRect->setChecked(true);
        attrTextSettingBar->setVisible(false);
        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    }
    //already in draw rectange state, goto no draw type state
    else
    {
        drawGeoType=drawNone;
        actDrawRect->setChecked(false);
        attrLineSettingBar->setVisible(false);
    }
    //drawFrom = drawTo;
    resetDrawStatusValues();
    update();
}

void CaptureWidget::drawEllipseAct(/*bool bToggled*/)
{
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }
    drawToTargetPixmap();
    //no draw Ellipse state,goto draw ellipse state
    if(drawGeoType!=drawEllipse)
    {
        drawGeoType=drawEllipse;
        actDrawEllipse->setChecked(true);
        attrTextSettingBar->setVisible(false);
        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    }
    //already in draw ellipse state, goto no draw type state
    else
    {
        drawGeoType=drawNone;
        actDrawEllipse->setChecked(false);
        attrLineSettingBar->setVisible(false);
    }
    //drawFrom = drawTo;
    resetDrawStatusValues();
    update();
}

void CaptureWidget::drawArrowAct()
{
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }
    drawToTargetPixmap();
    //no draw arrow state,goto draw Arrow state
    if(drawGeoType!=drawArrow)
    {
        drawGeoType=drawArrow;
        actDrawArrow->setChecked(true);
        attrTextSettingBar->setVisible(false);
        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    }
    //already in draw arrow state, goto no draw type state
    else
    {
        drawGeoType=drawNone;
        actDrawArrow->setChecked(false);
        attrLineSettingBar->setVisible(false);
    }
    //drawFrom = drawTo;
    resetDrawStatusValues();
    update();
}

void CaptureWidget::drawTextAct()
{
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }
    drawToTargetPixmap();
    //no draw text state,goto draw Arrow state
    if(drawGeoType!=drawText)
    {
        drawGeoType=drawText;
        actDrawText->setChecked(true);
        attrLineSettingBar->setVisible(false);
        ShowAttrExtToolBar(rtPickRect,attrTextSettingBar);
    }
    //already in draw text state, goto no draw type state
    else
    {
        drawGeoType=drawNone;
        actDrawText->setChecked(false);
        attrTextSettingBar->setVisible(false);
    }
    //drawFrom = drawTo;
    resetDrawStatusValues();
    update();
}

void CaptureWidget::drawRamLineAct(/*bool bToggled*/)
{
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }

    drawToTargetPixmap();
    //not draw random line,goto draw random line
    if(drawGeoType!=drawRamLine)
    {
        drawGeoType=drawRamLine;
        actDrawRandomLine->setChecked(true);
        attrTextSettingBar->setVisible(false);
        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    }
    //already in draw random line,goto none
    else
    {
        drawGeoType=drawNone;
        actDrawRandomLine->setChecked(false);
        attrLineSettingBar->setVisible(false);
    }
    //drawFrom = drawTo;
    resetDrawStatusValues();
    update();
}

//copy image into clip box
void CaptureWidget::copyToClipboxAct()
{
    drawToTargetPixmap();
    QClipboard *tmpClipboard = QApplication::clipboard();
    tmpClipboard->clear(QClipboard::Clipboard);
    tmpClipboard->setPixmap(bmpCapture);

    quitAct();
}

//save image into file.
void CaptureWidget::saveToFileAct()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("Save Picture"),QDir::currentPath(),tr("Images (*.jpg *.png *.bmp)"));
    if(fileName.isNull())
        return;
    drawToTargetPixmap();
    bmpCapture.save(fileName);
    quitAct();
}

void CaptureWidget::quitAct()
{
    emit exitCapture(bmpCapture);
    setVisible(false);
    resetPickStatus();
    selectorBoxes.reset();
    bmpCapture     = QPixmap();
    bmpDeskCapture = QPixmap();
}

bool CaptureWidget::initShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;

    if(evt->button()==Qt::LeftButton && MouseOperation==PressEvent) //begin select target area.
    {
        //begin selecting
        selectorBoxes.reset();
        selectorBoxes.setBeginPoint(evt->pos());
        controlValue = moveControlnone;

        currentShotState = beginShot; //设置当前状态为beginShot状态
        setCursor(Qt::CrossCursor);   //设置十字光标
        bProcessed = true;
    }
    else if(evt->button()==Qt::RightButton && MouseOperation==PressEvent) //release target area.
    {
        quitAct();
        bProcessed = true;
    }
    //    else if(MouseOperation==MoveEvent)
    //    {
    //        welcomeTipPosition = evt->pos();
    //        bProcessed = true;
    //    }
    return bProcessed;
}

bool CaptureWidget::beginShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;
    if(MouseOperation==MoveEvent)
    {
        //in selecting
        selectorBoxes.setEndPoint( evt->pos());
        rtPickRect = selectorBoxes.geometry();//selectorBoxes.getSelectRect();
        bmpCapture = bmpDeskCapture.copy(rtPickRect);
        selectorBoxes.setControlPoint8(rtPickRect);
        bProcessed = true;
    }
    // two time lb button press set the target area
    //    else if(evt->button()==Qt::LeftButton && MouseOperation == PressEvent)
    //    {
    //        selectorBoxes.setEndPoint( evt->pos());
    //        rtPickRect = selectorBoxes.geometry();
    //        bmpCapture = bmpDeskCapture.copy(rtPickRect);

    //        setCursor(Qt::OpenHandCursor);
    //        currentShotState = finishShot;
    //        this->showToolbars(rtPickRect);

    //        bProcessed = true;
    //    }
    //drag set target area
    else if(evt->button()==Qt::LeftButton && MouseOperation == ReleaseEvent)
    {
        //selecting over
        QPoint pos = selectorBoxes.getBeginPoint();
        QRect rect(pos,evt->pos());

        if(qAbs(rect.width())<10|| qAbs(rect.height())<10)
        {
            resetPickStatus();//reset currentShotState controlValue etc
            resetDrawStatusValues();
            selectorBoxes.reset();
            bProcessed = true;
            setCursor(colorCursor);
            return bProcessed;
        }
        selectorBoxes.setEndPoint( evt->pos());
        rtPickRect = selectorBoxes.geometry();
        bmpCapture = bmpDeskCapture.copy(rtPickRect);

        currentShotState = finishShot;
        this->showToolbars(rtPickRect);
        setCursor(colorCursor);
        //setCursor(Qt::ArrowCursor);

        bProcessed = true;
    }
    return bProcessed;
}

bool CaptureWidget::finishShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;
    if(evt->button()==Qt::RightButton && MouseOperation == ReleaseEvent)
    {
        //cancel the select rectange
        if(!selectorBoxes.geometry().contains(evt->pos()))
        {
            resetPickStatus();//reset currentShotState controlValue etc
            resetDrawStatusValues();
            selectorBoxes.reset();
            bProcessed = true;
            setCursor(colorCursor);
            //setCursor(Qt::ArrowCursor);
        }
    }
    else if(evt->button()==Qt::LeftButton && MouseOperation == PressEvent)
    {
        //whole target area adjust geometry
        if(selectorBoxes.inSelectRect(evt->pos()) &&
                selectorBoxes.getMoveControlPointID(evt->pos())==moveControlnone)
        {
            //启用开始移动选取选项,beginMoveShot状态
            currentShotState = beginMoveShot;
            selectorBoxes.setMoveBeginPoint(evt->pos());
            setCursor(Qt::ClosedHandCursor);

            mainToolbar->setVisible(false);
            bProcessed = true;
        }
        else if(selectorBoxes.getMoveControlPointID(evt->pos())!=moveControlnone)
        {
            //开始移动控制点
            currentShotState = beginControl;
            controlValue     = selectorBoxes.getMoveControlPointID(evt->pos());
            selectorBoxes.setMoveBeginPoint(evt->pos());
            updateMouseShape(controlValue);

            showToolbars(rtPickRect);
            bProcessed = true;
        }
        else //not in select rectange
        {
            setCursor(colorCursor);
            //setCursor(Qt::ArrowCursor);
        }
    }
    return bProcessed;
}

bool CaptureWidget::beginMoveShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;
    if(MouseOperation == MoveEvent)
    {
        //move the select rectange
        selectorBoxes.setMoveEndPoint(evt->pos());
        selectorBoxes.MovedGeometry(rtDeskCapture);
        rtPickRect = selectorBoxes.geometry();
        bmpCapture = bmpDeskCapture.copy(rtPickRect);
        selectorBoxes.setControlPoint8(rtPickRect);

        bProcessed = true;
    }
    else if(evt->button()==Qt::LeftButton && MouseOperation == ReleaseEvent)
    {
        //enter the finishshot ,set the select pixmap
        currentShotState = finishShot;

        selectorBoxes.setMoveEndPoint(evt->pos());
        selectorBoxes.MovedGeometry(rtDeskCapture);
        rtPickRect = selectorBoxes.geometry();
        bmpCapture = bmpDeskCapture.copy(rtPickRect);
        selectorBoxes.setControlPoint8(rtPickRect);

        showToolbars(rtPickRect);
        bProcessed = true;
    }
    return bProcessed;
}

bool CaptureWidget::beginControlHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;
    if(MouseOperation == MoveEvent)
    {
        //adjust the picker boxes
        selectorBoxes.setMoveEndPoint(evt->pos());
        rtPickRect = selectorBoxes.getMoveControlSelectedRect(controlValue);
        bmpCapture = bmpDeskCapture.copy(rtPickRect);
        selectorBoxes.setControlPoint8(rtPickRect);
        bProcessed = true;
    }
    else if(evt->button()==Qt::LeftButton && MouseOperation == ReleaseEvent)
    {
        //enter the finishShot,set the select rectange pixmap
        currentShotState = finishShot;
        selectorBoxes.setMoveEndPoint(evt->pos());
        rtPickRect = selectorBoxes.getMoveControlSelectedRect(controlValue);
        bmpCapture = bmpDeskCapture.copy(rtPickRect);
        selectorBoxes.setControlPoint8(rtPickRect);

        showToolbars(rtPickRect);
        bProcessed = true;
    }
    return bProcessed;
}

bool CaptureWidget::editShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;
    if(evt->button()==Qt::LeftButton)
    {
        if(MouseOperation==PressEvent) //begin draw
        {
            if(rtPickRect.contains(evt->pos()))
            {
                //                drawToTargetPixmap();

                drawFrom = evt->pos();
                drawTo = drawFrom;
                if(drawGeoType==drawRamLine)
                {
                    drawRandomLines.push_back(evt->pos());
                }
                else if(drawGeoType==drawText)
                {
                    drawTo = showInputBox(rtPickRect,evt->pos());
                }
                else
                {
                    drawTo = drawFrom;
                }

                currentShotState = editBeginShot;
                drawOnce = true;
                bProcessed = true;
            }
        }
    }
    else if(evt->button()==Qt::RightButton)
    {
        if(!selectorBoxes.geometry().contains(evt->pos()))
        {
            resetPickStatus();
            resetDrawStatusValues();
            selectorBoxes.reset();
            currentShotState = initShot;
            mainToolbar->setVisible(false);
            attrLineSettingBar->setVisible(false);
            attrTextSettingBar->setVisible(false);
            bProcessed = true;
            setCursor(colorCursor);
            //setCursor(Qt::ArrowCursor);
        }
    }
    return bProcessed;
}

bool CaptureWidget::editBeginShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;
    if(MouseOperation==MoveEvent)
    {
        QPoint curPos = evt->pos();
        if(!rtPickRect.contains(curPos))
        {
            curPos = adjustPointIntoRect(curPos,rtPickRect);
        }
        if(drawGeoType==drawRamLine)
        {
            drawRandomLines.push_back(curPos);
            drawRandomLines.push_back(curPos);
            bProcessed = true;
        }
        else if(drawGeoType!=drawText && drawGeoType!=drawNone)
        {
            drawTo = curPos;
            bProcessed = true;
        }
    }
    else if(evt->button()==Qt::LeftButton && MouseOperation==ReleaseEvent)
    {
        QPoint curPos = evt->pos();

        if(!rtPickRect.contains(curPos))
        {
            curPos = adjustPointIntoRect(curPos,rtPickRect);
        }

        if(drawGeoType==drawRamLine)
        {
            drawRandomLines.push_back(evt->pos());
            currentShotState = editEndShot;
            bProcessed = true;
        }
        else if(drawGeoType==drawText)
        {
            currentShotState = editingShot;
            bProcessed = true;
        }
        else if(drawGeoType!=drawText && drawGeoType!=drawNone)
        {
            drawTo = curPos;
            currentShotState = editEndShot;
            bProcessed = true;
        }
    }

    return bProcessed;
}

bool CaptureWidget::editingShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    Q_UNUSED(evt)
    bool bProcessed = false;
    if(/*evt->button()==Qt::LeftButton && */MouseOperation==PressEvent)
    {
        QString tmpInputString = textInputBox->text();
        //textInputString = textInputBox->text();
        textInputBox->clear();
        textInputBox->setVisible(false);
        textInputBox->clearFocus();
        textInputString = tmpInputString;

        currentShotState = editEndShot;
        bProcessed = true;
    }
    //    else if(evt->button()==Qt::RButton && MouseOperation==PressEvent)
    //    {
    //        ;
    //    }

    return bProcessed;
}

bool CaptureWidget::editEndShotHandler(QMouseEvent *evt,MouseEventType MouseOperation)
{
    bool bProcessed = false;

    //confirm draw operation
    if(evt->button()==Qt::LeftButton && (MouseOperation==PressEvent||MouseOperation==DoubleClick))
    {
        if(rtPickRect.contains(evt->pos()))//serialize to target image
        {
            qDebug("serialize to target image\n");
            //            QPainter painter(&bmpCapture);
            //            painter.translate(rtPickRect.topLeft().x()*(-1.0),rtPickRect.topLeft().y()*(-1.0));
            //            drawGeometry(&painter);

            drawToTargetPixmap();
            resetDrawStatusValues();
            currentShotState = editShot;

            //            if(drawGeoType!=drawText)
            editShotHandler(evt,PressEvent);

            bProcessed = true;
        }
        if(MouseOperation==DoubleClick) //copy to clip box
        {
            copyToClipboxAct();
        }
    }
    else if(evt->button()==Qt::RightButton &&MouseOperation==PressEvent)
    {
        if(rtPickRect.contains(evt->pos()))
        {
            resetDrawStatusValues();
            currentShotState = editShot;
            bProcessed = true;
        }
    }
    return bProcessed;
}

void CaptureWidget::drawToTargetPixmap()
{
    if(rtPickRect.width()>0 && rtPickRect.height()>0 && drawGeoType!=drawNone)
    {
        QPainter painter(&bmpCapture);
        painter.translate(rtPickRect.topLeft().x()*(-1.0),rtPickRect.topLeft().y()*(-1.0));
        drawGeometry(&painter,false);
        resetDrawStatusValues();
    }
}

void CaptureWidget::showToolbars(QRect rectFrame)
{
    QSize sizeToolBar = mainToolbar->size();
    QRect rcWidget  = geometry();
    QPoint realPoint = rectFrame.bottomLeft();
    mainToolbar->setOrientation(Qt::Horizontal);
    mainToolbar->adjustSize();
    sizeToolBar = mainToolbar->size();

    //1,default :工具栏显示在窗口下边

    //2,如果下边空余区域太小,将工具栏显示到上边
    if(rcWidget.bottomLeft().y()<(rectFrame.bottomLeft().y()+sizeToolBar.height() + defaultSpaceSize))
    {
        //3,如果上边空余区域太小,将工具栏显示到frame框的左上角
        if(rcWidget.topLeft().y() > (rectFrame.topLeft().y() - sizeToolBar.height() - defaultSpaceSize))
        {
            realPoint.setX(rectFrame.topLeft().x() + defaultSpaceSize + infoTipSize.width());
            realPoint.setY(rectFrame.topLeft().y() + defaultSpaceSize);
        }
        else
        {
            sizeToolBar = mainToolbar->size();
            realPoint.setX(rectFrame.x()+ infoTipSize.width());
            realPoint.setY(rectFrame.y()-sizeToolBar.height()-defaultSpaceSize);
        }
    }
    else
    {
        realPoint.setX(rectFrame.bottomLeft().x());
        realPoint.setY(rectFrame.bottomLeft().y()+defaultSpaceSize);
    }
    //set main toolbar position and display
    mainToolbar->move(realPoint);
    mainToolbar->setVisible(true);
}

void CaptureWidget::ShowAttrExtToolBar(QRect rectFrame,QWidget* attrBar)
{
    QRect rcOrgToolBar = mainToolbar->geometry();
    QRect rcAttrToolBar= attrBar->geometry();
    QPoint realPoint   = rcOrgToolBar.bottomLeft();
    QPoint mainToolPoint = rcOrgToolBar.topLeft();

    //mainToolBar in top side
    if(rectFrame.topLeft().y()>rcOrgToolBar.bottomLeft().y())
    {
        //space area is small,move maintoolbar to top in-side.
        if(rtDeskCapture.topLeft().y()>(rcOrgToolBar.topLeft().y() - defaultSpaceSize - rcAttrToolBar.height()))
        {
            mainToolPoint.setX(rectFrame.topLeft().x() + defaultSpaceSize);
            mainToolPoint.setY(rectFrame.topLeft().y() + defaultSpaceSize);
            realPoint.setX(mainToolPoint.x());
            realPoint.setY(mainToolPoint.y()+defaultSpaceSize+rcOrgToolBar.height());
        }
        //attrBar display at top side.
        else
        {
            realPoint.setX( mainToolPoint.x());
            realPoint.setY( mainToolPoint.y()-defaultSpaceSize-rcAttrToolBar.height());
        }
    }
    //mainToolBar in top in-side
    else if((rectFrame.topLeft().y()<rcOrgToolBar.topLeft().y())
            && (rectFrame.bottomLeft().y() > rcOrgToolBar.bottomLeft().y()))
    {
        realPoint.setX( mainToolPoint.x());
        realPoint.setY( mainToolPoint.y() + defaultSpaceSize + rcOrgToolBar.height());
    }
    //mainToolBar in bottom side
    else if(rectFrame.bottomLeft().y()<rcOrgToolBar.topLeft().y())
    {
        //bottom space area is small. move maintoolbar to top side.
        if(rtDeskCapture.bottomLeft().y()<rcOrgToolBar.bottomLeft().y() + defaultSpaceSize + rcAttrToolBar.height())
        {
            //move into top in-side
            if(rtDeskCapture.topLeft().y()>(rectFrame.topLeft().y()-defaultSpaceSize-rcOrgToolBar.height()- defaultSpaceSize-rcAttrToolBar.height()))
            {
                mainToolPoint.setX(rectFrame.topLeft().x() + defaultSpaceSize);
                mainToolPoint.setY(rectFrame.topLeft().y() + defaultSpaceSize);
                realPoint.setX(mainToolPoint.x());
                realPoint.setY(mainToolPoint.y()+defaultSpaceSize+rcAttrToolBar.height());
            }
            //move to top side
            else
            {
                mainToolPoint.setX(rectFrame.topLeft().x() + infoTipSize.width());
                mainToolPoint.setY(rectFrame.topLeft().y() - defaultSpaceSize -rcOrgToolBar.height());
                realPoint.setX( mainToolPoint.x());
                realPoint.setY( mainToolPoint.y()-defaultSpaceSize-rcAttrToolBar.height());
            }
        }
        //attrBar display in bottom side.
        else
        {
            realPoint.setX(rcOrgToolBar.bottomLeft().x());
            realPoint.setY(rcOrgToolBar.bottomLeft().y() + defaultSpaceSize );
        }
    }
    mainToolbar->move(mainToolPoint);
    mainToolbar->setVisible(true);
    attrBar->move(realPoint);
    attrBar->setVisible(true);
}

void CaptureWidget::attrTextChanged()
{
    drawToTargetPixmap();
    textFont = QFont("system",attrTextSettingBar->getFontSize());
    textColorUsed= attrTextSettingBar->getFontColor();
    qDebug("font size changed!\n");
    update();
    setFocus();
}

void CaptureWidget::attrLineChanged()
{
    drawToTargetPixmap();
    linePen = QPen(attrLineSettingBar->getLineColor(),attrLineSettingBar->getLineWidth(),Qt::SolidLine,Qt::FlatCap);
    lineColorUsed = attrLineSettingBar->getLineColor();
    qDebug("line pen changed!\n");
    update();
}

QWidget* CaptureWidget::_Creator(QWidget *parent)
{
    return new CaptureWidget(parent);
}
