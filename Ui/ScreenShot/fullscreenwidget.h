#ifndef FULLSCREENWIDGET_H
#define FULLSCREENWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QPainter>
#include <QPoint>
#include <QAction>
#include <QMenu>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QClipboard>
#include <QDebug>
#include <QScreen>
#include <QLabel>
#include <QToolBar>
#include "qmath.h"

class FullScreenWidget : public QWidget
{
  Q_OBJECT

public:
    FullScreenWidget(bool bSimple = true); //���캯��
    ~FullScreenWidget();
    //��򵥵Ĳ���
    void start();


    QPixmap getFullScreenPixmap(); //��ȡȫ����Pixmap

    //���н�����״̬
    enum shotState
    {
        initShot,
        beginShot,
        finishShot,
        editShot,
        editEndShot,
        endShot,
        beginMoveShot,
        finishMoveShot,
        beginControl,
        finishControl
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

    //�ƶ�ѡ���е�8�����Ƶ㣬����˳ʱ�뷽������Ͽ��Ƶ㵽���п��Ƶ������Ϊ1��8
    enum controlPointEnum
    {
        moveControl0,
        moveControl1,
        moveControl2,
        moveControl3,
        moveControl4,
        moveControl5,
        moveControl6,
        moveControl7,
        moveControl8
    };

public slots:
    void loadBackgroundPixmap(const QPixmap &bgPixmap);//���ر���Pixmap�ۺ���
    void loadBackgroundPixmap(const QPixmap &bgPixmap, int x, int y, int width, int height); //���ر���pixmap�ۺ���������x,y,width,height
    void cancelSelectedRect(); //ȡ��ѡ������
    void savePixmap(); //��ѡȡ��Ϊ�ķ���
    void slotQuit();
    void finishScreen();

    //����
    void drawRectAct();
    void drawEllipseAct();
    void drawRamLineAct();
    void drawArrowAct();
    void drawTextAct();
    void drawGeometry(QPainter *painter);

signals:
    void finishPixmap(const QPixmap &finishPixmap); //�����ͼ���ͼƬ,�����źŸ�������

private:
    bool m_bSimple;

    //ѡ�����8����ѡȡ
    QRect tlRect; //���ϵ�
    QRect trRect; //���ϵ�
    QRect blRect; //���µ�
    QRect brRect; //���µ�
    QRect tcRect; //���е�
    QRect bcRect; //���е�
    QRect lcRect;//���е�
    QRect rcRect; //���е�

    QPainter painter;
    QPoint beginPoint,endPoint,moveBeginPoint,moveEndPoint;
    QRect selectedRect; //ѡ������
    QPixmap loadPixmap,shotPixmap;
    shotState currentShotState; //��ǰ�Ľ���״̬
    controlPointEnum controlValue; //��¼�ƶ����Ƶ��ֵ
    QAction *savePixmapAction; //����ͼƬ��Ϊ
    QAction *cancelAction; //ȡ��ѡȡ��Ϊ
    QAction *quitAction; //�˳�ѡȡ��Ϊ
    QMenu *contextMenu; //ѡ�������Ҽ��˵�

    QToolBar *mainToolbar;
    QActionGroup *actDraws;            //all draw operation in one group because only one draw type in working,
    QAction *actDrawRect;             //draw rectange starting or ending operation.
    QAction *actDrawEllipse;          //draw ellipse starting or ending operation.
    QAction *actDrawRandomLine;       //draw random line starting or ending operation.
    QAction *actDrawArrow;            //add arrow operation.
    QAction *actDrawText;             //add text operation.
    QAction *actOk;
    QAction *actSave;
    QAction *actQuit;

    drawItemType     drawGeoType;      //current draw operation type
    QPen             linePen;          //pen used by draw line
    QFont            textFont;
    QRect      rtTextInput;            //input box rectange.
    QString    textInputString;        //input box content.

    bool             drawOnce;         //once draw operation finish flag.
    QPoint           drawFrom;         //draw operation start point,for rectange,ellipse
    QPoint           drawTo;           //draw operation end point,for rectange,ellipse
    QVector<QPoint>  drawRandomLines;  //draw random line operate points.

    int screenwidth; //������Ļ�Ŀ��
    int screenheight; //������Ļ�ĸ߶�
    int screenx; //ѡ����X
    int screeny; //ѡ����Y
    int tipWidth,tipHeight,infoWidth,infoHeight; //���س�ʼ��Ŀ�ȣ��߶ȣ���ʾ������Ϣ�Ŀ�ȣ��߶�
    const qreal  defaultSpaceSize=2;
    QSize infoTipSize;

    QRect getSelectedRect(); //��ȡѡȡ
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint); //�����������ȡѡȡ����
    void initFullScreenWidget(); //��ʼ��ץȫ������ز���
    bool isInSelectedRect(const QPoint &point); //�жϸõ��Ƿ���ѡ������
    void initSelectedMenu();//��ʼ���Ҽ��˵�
    void drawTipsText(); //����Ļ�ϴ�ӡ��ʾ��Ϣ
    void drawSelectedPixmap(void); //����Ļ�ϻ�ѡȡ����Ļ
    void updateBeginEndPointValue(const QRect &rect);  //���ƶ�ѡȡ�󣬶�beginPoint,endPoint������������޸�
    void checkMoveEndPoint(); //���ƶ���ѡ�������ж�
    void draw8ControlPoint(const QRect &rect);
    void updateMouseShape(const QPoint &point); //�������ĵ�ǰ״̬
    void updateMoveControlMouseShape(controlPointEnum controlValue);
    controlPointEnum getMoveControlState(const QPoint &point); //��ȡ�ƶ����Ƶ�״̬
    QRect getMoveAllSelectedRect(void); //��ȡ�ƶ�����ѡ�е�ѡ��
    QRect getMoveControlSelectedRect(void);//��ȡ�ƶ����Ƶ��ѡ��
    int getMinValue(int num1, int num2);//��ȡ�������е���Сֵ
    void drawXYWHInfo(void); //��ӡѡȡ��x,y,h,wֵ��Ϣ
    void addTollbars();
    void showToolbars(QRect rectFrame);

    //��д���෽��
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
};
#endif // FULLSCREENWIDGET_H
