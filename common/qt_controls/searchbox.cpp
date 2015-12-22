#include "searchbox.h"
#include "ui_searchBox.h"
#include <QKeyEvent>

#define MenuDistance 3

searchBox::searchBox(QWidget *parent)
    : QFrame(parent), ui(new Ui::searchBox),
      m_oListWindow(this, Qt::Popup)
{
    ui->setupUi(this);
    connect(ui->lineEdit_input, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));
    connect(&m_oListWindow, SIGNAL(selectChanged(int)), this, SLOT(slot_recordSelected(int)));
    connect(&m_oListWindow, SIGNAL(extendItemClicked(int)), this, SLOT(slot_extendItemClicked(int)));

    m_iRecordSelected = -1;
    m_iExtendItemSelected = -1;

    m_oListWindow.setFocusPolicy(Qt::NoFocus);
    m_oListWindow.setFocusProxy(ui->lineEdit_input);
    m_oListWindow.setMouseTracking(true);
    m_oListWindow.installEventFilter(this);
    m_oListWindow.setItemHeight(30, 30);
    m_oListWindow.setWindowOpacity(0.96);

    ui->pushButton_clear->hide();
}

searchBox::~searchBox()
{
    clearRecord();

    delete ui;
}

void searchBox::slot_recordSelected(int iIndex)
{
    m_iRecordSelected = iIndex;
    emit recordSelected(iIndex);
}

void searchBox::slot_extendItemClicked(int iIndex)
{
    m_iExtendItemSelected = iIndex;
    emit extendItemSelected(iIndex);
}

void searchBox::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);

    const int iPixmapDistance = 5;
    const int iHeightDistance = 2;
    const int iControlDistance = 2;
    const int iControlHeight = height() - iHeightDistance * 2;

    ui->label_Picture->resize(iControlHeight, iControlHeight);
    ui->lineEdit_input->resize(width() - iControlHeight - iControlDistance, iControlHeight);
    ui->label_Picture->move(iPixmapDistance, iHeightDistance);
    ui->lineEdit_input->move(iPixmapDistance + iControlHeight + iControlDistance, iHeightDistance);
    ui->pushButton_clear->resize(height(), height());
    ui->pushButton_clear->move(width() - height(), 0);
    m_oListWindow.setWidth(width() - MenuDistance * 2);
}

void searchBox::enterEvent(QEvent *ev)
{
    QFrame::enterEvent(ev);

    ui->pushButton_clear->show();
    ui->pushButton_clear->raise();
}

void searchBox::leaveEvent(QEvent *ev)
{
    QFrame::leaveEvent(ev);
    ui->pushButton_clear->hide();
}

void searchBox::setRecord(const QList<searchboxData> &listRecord)
{
    clearRecord();
    m_data = listRecord;
    showListWindow();
}

void searchBox::showListWindow()
{
    m_oListWindow.setData(m_data);
    m_oListWindow.move(mapToGlobal(QPoint(MenuDistance, height())));

    m_oListWindow.setFocus();
    m_oListWindow.show();
}

void searchBox::clearRecord()
{
    m_data.clear();
    showListWindow();
    m_iRecordSelected = -1;
    m_iExtendItemSelected = -1;
}

bool searchBox::eventFilter(QObject *object, QEvent *ev)
{
    if (&m_oListWindow == object)
    {
        if (ev->type() == QEvent::KeyPress)
        {
            int key = static_cast<QKeyEvent*>(ev)->key();
            switch(key)
            {
            case Qt::Key_Escape:
                m_oListWindow.reject();
                ui->lineEdit_input->setFocus();
                return true;

            default:
                ui->lineEdit_input->setFocus();
                ui->lineEdit_input->event(ev);
                break;
            }
        }
    }

    return QFrame::eventFilter(object, ev);
}

void searchBox::setMaxShowRecord(int max)
{
    m_oListWindow.setMaxShowItem(max);
}

bool searchBox::getItemData(int iIndex, searchboxData &data)
{
    if (iIndex < 0 || iIndex >= m_data.size())
    {
        return false;
    }

    data = m_data[iIndex];

    return true;
}

int searchBox::getRecordCurrentSelected()
{
    return m_iRecordSelected;
}

void searchBox::setExternItemData(const QList<searchExtendItemData> &listData)
{
    m_oListWindow.setExternItemData(listData);
}

void searchBox::on_pushButton_clear_clicked()
{
    ui->lineEdit_input->clear();
}
