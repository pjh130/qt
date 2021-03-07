#include "fullscreenwidget.h"
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>

FullScreenWidget::FullScreenWidget(bool bSimple)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowState(Qt::WindowActive|Qt::WindowFullScreen);
    m_bSimple = bSimple;
    tipWidth = 300; //��ܰ��ʾ��Ŀ��
    tipHeight = 100; //��ܰ��ʾ��ĸ߶�
    infoWidth = 100; //������Ϣ��Ŀ��
    infoHeight = 70; //������Ϣ��ĸ߶�
    infoTipSize = QSize(infoWidth,infoHeight);

    if (true)
    {
        addTollbars();
    }

    initFullScreenWidget();
}

FullScreenWidget::~FullScreenWidget()
{
    qDebug()<<"FullScreenWidget::~FullScreenWidget()";
}

void FullScreenWidget::initSelectedMenu()
{
    savePixmapAction = new QAction(QStringLiteral("����ѡ��"),this);
    cancelAction = new QAction(QStringLiteral("��ѡ"),this);
    quitAction = new QAction(QStringLiteral("�˳�"),this);
    contextMenu = new QMenu(this);

    connect(savePixmapAction,SIGNAL(triggered()),this,SLOT(savePixmap()));
    connect(cancelAction,SIGNAL(triggered()),this,SLOT(cancelSelectedRect()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(slotQuit()));
}

void FullScreenWidget::finishScreen()
{
    if (m_bSimple)
    {
        if (!shotPixmap.isNull())
        {
            //ͬʱ�ѽ�ͼ�ŵ�ճ����
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->clear(QClipboard::Clipboard);
            clipboard->setPixmap(shotPixmap);
        }
    }
    emit finishPixmap(shotPixmap);
    //    hide();
    close();
}

void FullScreenWidget::slotQuit()
{
    finishScreen();
}

void FullScreenWidget::savePixmap()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,QStringLiteral("����ͼƬ"),QDir::currentPath(),tr("Images (*.jpg *.png *.bmp)"));
    if(fileName.isNull())
        return;

    if (fileName.isEmpty())
    {
        currentShotState = finishShot;
        return;
    }
    shotPixmap.save(fileName);
    finishScreen();
}

void FullScreenWidget::start()
{
    QPixmap bgPixmap = getFullScreenPixmap();;
    QDesktopWidget *pDecktopWidget = QApplication::desktop();
    int width = pDecktopWidget->size().width();
    int height = pDecktopWidget->size().height();

    loadBackgroundPixmap(bgPixmap, 0, 0, width, height);
}
void FullScreenWidget::loadBackgroundPixmap(const QPixmap &bgPixmap)
{
    QDesktopWidget *pDecktopWidget = QApplication::desktop();
    int width = pDecktopWidget->size().width();
    int height = pDecktopWidget->size().height();

    loadBackgroundPixmap(bgPixmap, 0, 0, width, height);
}

void FullScreenWidget::loadBackgroundPixmap(const QPixmap &bgPixmap, int x, int y, int width, int height)
{
    loadPixmap = bgPixmap;
    screenx = x;
    screeny = y;
    screenwidth = width;
    screenheight = height;
    initFullScreenWidget();
}

QPixmap FullScreenWidget::getFullScreenPixmap()
{
    initFullScreenWidget();
    QPixmap result = QPixmap();
    result = QPixmap::grabWindow(QApplication::desktop()->winId()); //ץȡ��ǰ��Ļ��ͼƬ

    return result;
}

void FullScreenWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QColor shadowColor;
    shadowColor= QColor(0,0,0,100); //��Ӱ��ɫ����
    painter.begin(this); //�����ػ�

    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine,Qt::FlatCap));//���û���
    painter.drawPixmap(screenx,screeny,loadPixmap); //������ͼƬ����������
    painter.fillRect(screenx,screeny,screenwidth,screenheight,shadowColor); //��Ӱ��Ч��

    switch(currentShotState)
    {
    case initShot:
        drawTipsText();
        break;

    case beginShot:
    case finishShot:
        selectedRect = getRect(beginPoint,endPoint); //��ȡѡ��
        drawSelectedPixmap();
        break;
    case editShot:
        qDebug()<<"FullScreenWidget::paintEvent editShot";
        drawSelectedPixmap();

        if(drawOnce){
            drawGeometry(&painter);
//           QPainter p(&shotPixmap);
//           QPoint x = drawFrom - selectedRect.topLeft();
//           QPoint y = selectedRect.bottomRight() - drawTo;

//           qDebug()<<"shotPixmap: "<<shotPixmap.rect();
//           qDebug()<<"QRect: "<<QRect(x, y);
//           p.drawRect(QRect(x, y));
//           p.save();
        }
        break;
    case beginMoveShot:
    case finishMoveShot:
        selectedRect = getMoveAllSelectedRect(); //��ȡѡ��
        drawSelectedPixmap();
        break;

    case beginControl:
    case finishControl:
        selectedRect = getMoveControlSelectedRect();
        drawSelectedPixmap();
        break;

    default:
        break;
    }
    drawXYWHInfo(); //��ӡ������Ϣ
    painter.end();  //�ػ����

    if(currentShotState == finishMoveShot || currentShotState == finishControl)
    {
        updateBeginEndPointValue(selectedRect); //���ƶ���ѡ���󣬸���beginPoint,endPoint;Ϊ��һ���ƶ���׼������
    }

}

void FullScreenWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        initFullScreenWidget();
        finishScreen();
    }
}

void FullScreenWidget::mousePressEvent(QMouseEvent *event)
{
    //����ʼ�����϶�����ѡ������ʱ,ȷ����ʼѡȡ��beginPoint����
    if(event->button() == Qt::LeftButton && currentShotState == initShot)
    {
        currentShotState = beginShot; //���õ�ǰ״̬ΪbeginShot״̬
        beginPoint = event->pos();
    }

    //�༭
    if(event->button() == Qt::LeftButton && currentShotState == editShot)
    {
        qDebug()<<"FullScreenWidget::mousePressEvent currentShotState == editShot";
        drawOnce = true;
        drawFrom = event->pos();
    }

    //�ƶ�ѡ���ı�ѡ��������λ��
    if(event->button() == Qt::LeftButton && isInSelectedRect(event->pos()) &&
            getMoveControlState(event->pos()) == moveControl0 && currentShotState != editShot)
    {
        currentShotState = beginMoveShot; //���ÿ�ʼ�ƶ�ѡȡѡ��,beginMoveShot״̬
        moveBeginPoint = event->pos();
    }
    //�ƶ����Ƶ�ı�ѡ����С
    if(event->button() == Qt::LeftButton && getMoveControlState(event->pos()) != moveControl0)
    {
        currentShotState = beginControl; //��ʼ�ƶ����Ƶ�
        controlValue = getMoveControlState(event->pos());
        moveBeginPoint = event->pos();
    }

    if(event->button() == Qt::RightButton && !isInSelectedRect(event->pos()))
    {
        if (currentShotState == beginShot || currentShotState == initShot)
        {
            finishScreen();
        } else {
            cancelSelectedRect();
        }
    }
}

void FullScreenWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && currentShotState == beginShot)
    {
        currentShotState = finishShot;
        endPoint = event->pos();

        showToolbars(QRect(beginPoint, endPoint));
        update();
    }

    //�༭
    if(event->button() == Qt::LeftButton && currentShotState == editShot)
    {
        drawTo = event->pos();
        update();
        drawOnce = false;
    }

    if(event->button() == Qt::LeftButton && currentShotState == beginMoveShot)
    {
        currentShotState = finishMoveShot;
        moveEndPoint = event->pos();
        update();
    }

    //��ǰ״̬ΪbeginControl״̬ʱ������״̬ΪfinishControl
    if(event->button() == Qt::LeftButton && currentShotState == beginControl)
    {
        currentShotState = finishControl;
        moveEndPoint = event->pos();
        update();
    }
}

void FullScreenWidget::mouseMoveEvent(QMouseEvent *event)
{
    //���϶�ʱ����̬�ĸ�����ѡ�������
    if(currentShotState == beginShot)
    {
        endPoint = event->pos();
        update();
    }

    //�༭
    if(currentShotState == editShot)
    {
        drawTo = event->pos();
        if (drawOnce)
        {
            update();
        }
    }

    //��ȷ��ѡ���󣬶�ѡ�������ƶ�����
    if(currentShotState == beginMoveShot || currentShotState == beginControl)
    {
        moveEndPoint = event->pos();
        showToolbars(QRect(selectedRect.topLeft(), selectedRect.bottomRight()));
        update();
    }

    updateMouseShape(event->pos()); //�޸�������״
    setMouseTracking(true);
}

void FullScreenWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(currentShotState == finishShot || currentShotState == finishMoveShot || currentShotState == finishControl)
    {
        finishScreen();
    }
}

QRect FullScreenWidget::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x,y,width,height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    return QRect(x,y,width,height);
}

void FullScreenWidget::initFullScreenWidget()
{
    currentShotState = initShot;
    controlValue = moveControl0;
    beginPoint =QPoint(0,0);
    endPoint = QPoint(0,0);
    moveBeginPoint = QPoint(0,0);
    moveEndPoint = QPoint(0,0);

    tlRect = QRect(0,0,0,0); //���ϵ�
    trRect = QRect(0,0,0,0); //���ҵ�
    blRect = QRect(0,0,0,0); //���µ�
    brRect = QRect(0,0,0,0); //���µ�
    tcRect = QRect(0,0,0,0); //���е�
    bcRect = QRect(0,0,0,0); //���е�
    lcRect = QRect(0,0,0,0); //���е�
    rcRect = QRect(0,0,0,0); //���е�

    setCursor(Qt::CrossCursor);
}

bool FullScreenWidget::isInSelectedRect(const QPoint &point)
{
    int x,y;
    QRect selectedRect;
    if(currentShotState == initShot || currentShotState == beginShot)
        return false;

    selectedRect = getSelectedRect();
    x = point.x();
    y = point.y();

    return selectedRect.contains(x,y);
}

void FullScreenWidget::addTollbars()
{
    mainToolbar    =new QToolBar(tr("main tool bar"),this);
    mainToolbar->setIconSize (QSize(16,16));
    //set tool bar's attribute
    mainToolbar->setAutoFillBackground(true);
    mainToolbar->setFloatable(true);
    mainToolbar->setMovable(false);
    mainToolbar->setVisible(false);

    actOk    = new QAction(tr("OK"),this);
    actSave  = new QAction(tr("Save"),this);
    actQuit = new QAction(tr("Quit"),this);
    //group
    actDraws         =new QActionGroup(this);
    actDrawRect      =new QAction(tr("Rectange"),this);
    actDrawEllipse   =new QAction(tr("Ellipse"),this);
    actDrawRandomLine=new QAction(tr("Brush"),this);
    actDrawArrow     =new QAction(tr("Arrow"),this);
    actDrawText      =new QAction(tr("T"),this);
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

    //add icon
    actDrawRect->setIcon(QIcon(QString::fromUtf8(":/Rectange.png")));
    actDrawEllipse->setIcon(QIcon(QString::fromUtf8(":/Ellipse.png")));
    actDrawRandomLine->setIcon(QIcon(QString::fromUtf8(":/Brush01.png")));
    actDrawArrow->setIcon(QIcon(QString::fromUtf8(":/Arrow.png")));
    actDrawText->setIcon(QIcon(QString::fromUtf8(":/Text.png")));
    actOk->setIcon(QIcon(QString::fromUtf8(":/Copy.png")));
    actSave->setIcon(QIcon(QString::fromUtf8(":/Save.png")));
    actQuit->setIcon(QIcon(QString::fromUtf8(":/Quit.png")));
    //add action
    mainToolbar->addActions(actDraws->actions());
    mainToolbar->addAction(actSave);
    mainToolbar->addAction(actQuit);
    mainToolbar->addAction(actOk);

    //add connect
    connect(actOk,SIGNAL(triggered()),this,SLOT(finishScreen()));
    connect(actSave,SIGNAL(triggered()),this,SLOT(savePixmap()));
    connect(actQuit,SIGNAL(triggered()),this,SLOT(slotQuit()));
    //group
    connect(actDrawRect,SIGNAL(triggered()),this,SLOT(drawRectAct()));
    connect(actDrawEllipse,SIGNAL(triggered()),this,SLOT(drawEllipseAct()));
    connect(actDrawRandomLine,SIGNAL(triggered()),this,SLOT(drawRamLineAct()));
    connect(actDrawArrow,SIGNAL(triggered()),this,SLOT(drawArrowAct()));
    connect(actDrawText,SIGNAL(triggered()),this,SLOT(drawTextAct()));
}

void FullScreenWidget::drawRectAct(/*bool bToggled*/)
{
    drawOnce = false;
    qDebug()<<"FullScreenWidget::drawRectAct";
    //enter the edit state
    if(currentShotState==finishShot)
    {
        qDebug()<<"FullScreenWidget::drawRectAct 1";
        currentShotState = editShot;
    } else {
        qDebug()<<"FullScreenWidget::drawRectAct 2";
    }
    drawGeoType=drawRectange;
    actDrawRect->setChecked(true);
    //    drawToTargetPixmap();
    //    //not in draw rectange state, goto rectange state
    //    if(drawGeoType!=drawRectange)
    //    {
    //        drawGeoType=drawRectange;
    //        actDrawRect->setChecked(true);
    //        attrTextSettingBar->setVisible(false);
    //        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    //    }
    //    //already in draw rectange state, goto no draw type state
    //    else
    //    {
    //        drawGeoType=drawNone;
    //        actDrawRect->setChecked(false);
    //        attrLineSettingBar->setVisible(false);
    //    }
    //    //drawFrom = drawTo;
    //    resetDrawStatusValues();
    update();
}

void FullScreenWidget::drawEllipseAct(/*bool bToggled*/)
{
    return;
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }
    //    drawToTargetPixmap();
    //    //no draw Ellipse state,goto draw ellipse state
    //    if(drawGeoType!=drawEllipse)
    //    {
    //        drawGeoType=drawEllipse;
    //        actDrawEllipse->setChecked(true);
    //        attrTextSettingBar->setVisible(false);
    //        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    //    }
    //    //already in draw ellipse state, goto no draw type state
    //    else
    //    {
    //        drawGeoType=drawNone;
    //        actDrawEllipse->setChecked(false);
    //        attrLineSettingBar->setVisible(false);
    //    }
    //    //drawFrom = drawTo;
    //    resetDrawStatusValues();
    update();
}

void FullScreenWidget::drawArrowAct()
{
    return;
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }
    //    drawToTargetPixmap();
    //    //no draw arrow state,goto draw Arrow state
    //    if(drawGeoType!=drawArrow)
    //    {
    //        drawGeoType=drawArrow;
    //        actDrawArrow->setChecked(true);
    //        attrTextSettingBar->setVisible(false);
    //        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    //    }
    //    //already in draw arrow state, goto no draw type state
    //    else
    //    {
    //        drawGeoType=drawNone;
    //        actDrawArrow->setChecked(false);
    //        attrLineSettingBar->setVisible(false);
    //    }
    //    //drawFrom = drawTo;
    //    resetDrawStatusValues();
    update();
}

void FullScreenWidget::drawTextAct()
{
    return;
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }
    //    drawToTargetPixmap();
    //    //no draw text state,goto draw Arrow state
    //    if(drawGeoType!=drawText)
    //    {
    //        drawGeoType=drawText;
    //        actDrawText->setChecked(true);
    //        attrLineSettingBar->setVisible(false);
    //        ShowAttrExtToolBar(rtPickRect,attrTextSettingBar);
    //    }
    //    //already in draw text state, goto no draw type state
    //    else
    //    {
    //        drawGeoType=drawNone;
    //        actDrawText->setChecked(false);
    //        attrTextSettingBar->setVisible(false);
    //    }
    //    //drawFrom = drawTo;
    //    resetDrawStatusValues();
    update();
}

void FullScreenWidget::drawRamLineAct(/*bool bToggled*/)
{
    return;
    //enter the edit state
    if(currentShotState==finishShot)
    {
        currentShotState = editShot;
    }

    //    drawToTargetPixmap();
    //    //not draw random line,goto draw random line
    //    if(drawGeoType!=drawRamLine)
    //    {
    //        drawGeoType=drawRamLine;
    //        actDrawRandomLine->setChecked(true);
    //        attrTextSettingBar->setVisible(false);
    //        ShowAttrExtToolBar(rtPickRect,attrLineSettingBar);
    //    }
    //    //already in draw random line,goto none
    //    else
    //    {
    //        drawGeoType=drawNone;
    //        actDrawRandomLine->setChecked(false);
    //        attrLineSettingBar->setVisible(false);
    //    }
    //    //drawFrom = drawTo;
    //    resetDrawStatusValues();
    update();
}

void FullScreenWidget::showToolbars(QRect rectFrame)
{
    //    QSize sizeToolBar = mainToolbar->size();
    QRect rcWidget  = geometry();
    QPoint realPoint = rectFrame.bottomLeft();
    mainToolbar->setOrientation(Qt::Horizontal);
    mainToolbar->setMinimumSize(48, 36);
    mainToolbar->adjustSize();
    QSize sizeToolBar = mainToolbar->size();

    //1,default :��������ʾ�ڴ����±�

    //2,����±߿�������̫С,����������ʾ���ϱ�
    if(rcWidget.bottomLeft().y()<(rectFrame.bottomLeft().y()+sizeToolBar.height() + defaultSpaceSize))
    {
        //3,����ϱ߿�������̫С,����������ʾ��frame������Ͻ�
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

void FullScreenWidget::cancelSelectedRect()
{
    mainToolbar->setVisible(false);
    initFullScreenWidget();
    update(); //�����ػ棬��ѡȡ����ȥ��
}

void FullScreenWidget::contextMenuEvent(QContextMenuEvent *event)
{
    //��ģʽ�Ͳ�����ʾ�˵���
    if (m_bSimple)
    {
        return;
    }

    initSelectedMenu();
    if(isInSelectedRect(event->pos())){
        contextMenu->addAction(savePixmapAction);
    } else{
        contextMenu->addAction(cancelAction);
        contextMenu->addAction(quitAction);
    }

    contextMenu->exec(event->pos());
}

void FullScreenWidget::drawTipsText()
{
    int x = (screenwidth - tipWidth)/2;
    int y = (screenheight - tipHeight)/2;
    QColor color = QColor(100,100,100,200);
    QRect rect = QRect(x,y,tipWidth,tipHeight);
    QString strTipsText;
    if (m_bSimple)
    {
        strTipsText = QString(QStringLiteral("��ܰ��ʾ\n����϶����н���;\n�����������Ҽ�ȡ��;ESC�˳�;"));
    } else {
        strTipsText = QString(QStringLiteral("��ܰ��ʾ\n����϶����н���;�����������Ҽ�����;\n�����������Ҽ�ȡ��;ESC�˳�;"));
    }


    painter.fillRect(rect,color);
    painter.setPen(QPen(Qt::white));//���û��ʵ���ɫΪ��ɫ
    painter.drawText(rect,Qt::AlignCenter,strTipsText);

}

QRect FullScreenWidget::getSelectedRect()
{
    if(currentShotState == beginMoveShot){
        return getMoveAllSelectedRect();
    }
    else if(currentShotState == beginControl){
        return getMoveControlSelectedRect();
    }
    else{
        return getRect(beginPoint,endPoint);
    }
}

void FullScreenWidget::updateBeginEndPointValue(const QRect &rect)
{
    beginPoint = rect.topLeft();
    endPoint = rect.bottomRight();

    moveBeginPoint = QPoint(0,0);
    moveEndPoint = QPoint(0,0);
}

void FullScreenWidget::checkMoveEndPoint()
{
    int x,y;
    QRect selectedRect = getRect(beginPoint, endPoint);
    QPoint bottomRightPoint = selectedRect.bottomRight();
    x = moveEndPoint.x() - moveBeginPoint.x();
    y = moveEndPoint.y() - moveBeginPoint.y();

    if(x + selectedRect.x() < 0){ //���ƶ���X����С����ʱ�������ѡ����ʧ��������moveEndPoint��X�������ֵ�����и�ֵ
        moveEndPoint.setX(qAbs(selectedRect.x()-moveBeginPoint.x()));
    }

    if(y + selectedRect.y() < 0){ //���ƶ���Y����С����ʱ�������ѡ����ʧ��������moveEndPoint��Y�������ֵ�����и�ֵ
        moveEndPoint.setY(qAbs(selectedRect.y() - moveBeginPoint.y()));
    }

    if(x + bottomRightPoint.x() > screenwidth){ //���ƶ�ѡ���󣬳��ֳ���������Ļ������ʱ������moveEndPoint��X���������
        moveEndPoint.setX(screenwidth - bottomRightPoint.x() + moveBeginPoint.x());
    }

    if(y + bottomRightPoint.y() > screenheight){ //���ƶ�ѡ���󣬳��ֳ���������Ļ������ʱ������moveEndPoint��Y���������ֵ
        moveEndPoint.setY(screenheight - bottomRightPoint.y() + moveBeginPoint.y());
    }
}

void FullScreenWidget::draw8ControlPoint(const QRect &rect)
{
    int x,y;
    QColor color= QColor(0,0,255); //�������ɫ����
    QPoint tlPoint = rect.topLeft(); //���ϵ�
    QPoint trPoint = rect.topRight(); //���ϵ�
    QPoint blPoint = rect.bottomLeft(); //���µ�
    QPoint brPoint = rect.bottomRight(); //���µ�

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

    tlRect = QRect(tlPoint.x()-2,tlPoint.y()-2,6,6); //���ϵ�
    trRect = QRect(trPoint.x()-2,trPoint.y()-2,6,6); //���ϵ�
    blRect = QRect(blPoint.x()-2,blPoint.y()-2,6,6); //���µ�
    brRect = QRect(brPoint.x()-2,brPoint.y()-2,6,6); //���µ�
    tcRect = QRect(tcPoint.x()-2,tcPoint.y()-2,6,6); //���е�
    bcRect = QRect(bcPoint.x()-2,bcPoint.y()-2,6,6); //���е�
    lcRect = QRect(lcPoint.x()-2,lcPoint.y()-2,6,6);//���е�
    rcRect = QRect(rcPoint.x()-2,rcPoint.y()-2,6,6); //���е�

    painter.fillRect(tlRect,color);
    painter.fillRect(trRect,color);
    painter.fillRect(blRect,color);
    painter.fillRect(brRect,color);
    painter.fillRect(tcRect,color);
    painter.fillRect(bcRect,color);
    painter.fillRect(lcRect,color);
    painter.fillRect(rcRect,color);
}

void FullScreenWidget::updateMouseShape(const QPoint &point)
{
    switch(currentShotState)
    {
    case initShot:
    case beginShot:
        setCursor(Qt::CrossCursor);
        break;
    case beginMoveShot:
        setCursor(Qt::OpenHandCursor);
        break;
    case finishShot:
    case finishMoveShot:
    case finishControl:
        if(getSelectedRect().contains(point))
        {
            setCursor(Qt::OpenHandCursor);
        } else {

            updateMoveControlMouseShape(getMoveControlState(point));
        }
        break;
    case beginControl:
        updateMoveControlMouseShape(controlValue); //���ú������ƶ�8�����Ƶ�������״̬�ĸı�
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

void FullScreenWidget::updateMoveControlMouseShape(controlPointEnum controlValue){
    switch(controlValue){
    case moveControl1:
    case moveControl5:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case moveControl2:
    case moveControl6:
        setCursor(Qt::SizeVerCursor);
        break;
    case moveControl3:
    case moveControl7:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case moveControl4:
    case moveControl8:
        setCursor(Qt::SizeHorCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

FullScreenWidget::controlPointEnum FullScreenWidget::getMoveControlState(const QPoint &point)
{
    FullScreenWidget::controlPointEnum result = moveControl0;
    if(currentShotState == initShot || currentShotState == beginShot)  {
        result = moveControl0;
    }
    else if(tlRect.contains(point)){
        result = moveControl1;
    }
    else if(tcRect.contains(point)){
        result = moveControl2;
    }
    else if(trRect.contains(point)){
        result = moveControl3;
    }
    else if(rcRect.contains(point)){
        result = moveControl4;
    }
    else if(brRect.contains(point)){
        result = moveControl5;
    }
    else if(bcRect.contains(point)){
        result = moveControl6;
    }
    else if(blRect.contains(point)){
        result = moveControl7;
    }
    else if(lcRect.contains(point)){
        result = moveControl8;
    }
    else{
        result = moveControl0;
    }

    return result;
}

QRect FullScreenWidget::getMoveAllSelectedRect(void)
{
    QRect result;
    QPoint tmpBeginPoint,tmpEndPoint;
    int moveX,moveY;
    checkMoveEndPoint(); //���ƶ�ѡ�������жϣ����ƶ���ѡ�������߽磬��ֹͣ�ƶ�
    moveX = moveEndPoint.x() - moveBeginPoint.x();
    moveY = moveEndPoint.y() - moveBeginPoint.y();
    tmpBeginPoint.setX(beginPoint.x() + moveX);
    tmpBeginPoint.setY(beginPoint.y() + moveY);
    tmpEndPoint.setX(endPoint.x() + moveX);
    tmpEndPoint.setY(endPoint.y() + moveY);

    result = getRect(tmpBeginPoint, tmpEndPoint);
    return result;
}

QRect FullScreenWidget::getMoveControlSelectedRect(void)
{
    int x,y,w,h;
    QRect rect = getRect(beginPoint,endPoint);
    QRect result;
    switch(controlValue){
    case moveControl1:
        result = getRect(rect.bottomRight(),moveEndPoint);
        return result;
        break;
    case moveControl2:
        x = rect.x();
        y = getMinValue(moveEndPoint.y(),rect.bottomLeft().y());
        w = rect.width();
        h = qAbs(moveEndPoint.y() - rect.bottomRight().y());
        break;
    case moveControl3:
        result = getRect(rect.bottomLeft(),moveEndPoint);
        return result;
        break;
    case moveControl4:
        x = getMinValue(rect.x(),moveEndPoint.x());
        y = rect.y();
        w = qAbs(rect.bottomLeft().x() - moveEndPoint.x());
        h = rect.height();
        break;
    case moveControl5:
        result = getRect(rect.topLeft(),moveEndPoint);
        return result;
        break;
    case moveControl6:
        x = rect.x();
        y = getMinValue(rect.y(),moveEndPoint.y());
        w = rect.width();
        h = qAbs(moveEndPoint.y() - rect.topLeft().y());
        break;
    case moveControl7:
        result = getRect(moveEndPoint,rect.topRight());
        return result;
        break;
    case moveControl8:
        x = getMinValue(moveEndPoint.x(),rect.bottomRight().x());
        y = rect.y();
        w = qAbs(rect.bottomRight().x() - moveEndPoint.x());
        h = rect.height();
        break;
    default:
        result = getRect(beginPoint,endPoint);
        return result;
        break;
    }

    return QRect(x,y,w,h); //��ȡѡ��
}

int FullScreenWidget::getMinValue(int num1, int num2)
{
    return num1<num2?num1:num2;
}

void FullScreenWidget::drawSelectedPixmap(void)
{
    painter.drawRect(selectedRect); //��ѡ�еľ��ο�
    shotPixmap = loadPixmap.copy(selectedRect);  //����ѡ����Pixmap
    if(selectedRect.width() > 0 && selectedRect.height()){
        painter.drawPixmap(selectedRect.topLeft(),shotPixmap); //��ѡ�������ͼƬ
    }
    draw8ControlPoint(selectedRect); //����ѡ����8�����Ƶ�
}

void FullScreenWidget::drawGeometry(QPainter *painter)
{
    if(drawGeoType==drawRectange)
    {
        qDebug()<<"FullScreenWidget::drawGeometry drawRectange";
        QRect rtDraw(drawFrom,drawTo);
        painter->save();
        painter->setPen(linePen);
        painter->drawRect(rtDraw);
        painter->restore();
        actDrawRect->setChecked(false);
    }
    else if(drawGeoType==drawEllipse)
    {
        QRect rtDraw(drawFrom,drawTo);
        painter->save();
        painter->setPen(linePen);
        painter->drawEllipse(rtDraw.center(),rtDraw.width()/2,rtDraw.height()/2);
        painter->restore();
    }
    else if(drawGeoType==drawRamLine)
    {
        painter->save();
        painter->setPen(linePen);
        painter->drawLines(drawRandomLines);
        painter->restore();}
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
        QFont orgFont = painter->font();
        painter->setFont(textFont);
        //        painter->setPen(textColorUsed);
        textInputString = "Hello world";
        painter->drawText(rtTextInput,textInputString,QTextOption(Qt::AlignVCenter));
        painter->setFont(orgFont);
    }
}

void FullScreenWidget::drawXYWHInfo(void)
{
    int x,y;
    QColor color = QColor(239,234,228,200);
    QRect rect;
    QString strTipsText;
    switch(currentShotState){
    case beginShot:
    case finishShot:
    case beginMoveShot:
    case finishMoveShot:
    case beginControl:
    case finishControl:
        x = selectedRect.x() + 5;
        y = (selectedRect.y() > infoHeight ? selectedRect.y()-infoHeight:selectedRect.y());
        rect = QRect(x,y,infoWidth,infoHeight);
        strTipsText = QString(QStringLiteral(" ������Ϣ\n x:%1 y:%2\n w:%3 h:%4")).arg(selectedRect.x(),4).arg(selectedRect.y(),4)
                .arg(selectedRect.width(),4).arg(selectedRect.height(),4);
        painter.fillRect(rect,color);
        painter.setPen(QPen(Qt::black));//���û��ʵ���ɫΪ��ɫ
        painter.drawText(rect,Qt::AlignLeft|Qt::AlignVCenter,strTipsText);
        break;
    default:
        break;
    }
}

