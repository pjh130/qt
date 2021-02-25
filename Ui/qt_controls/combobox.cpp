#include "combobox.h"
#include "ui_comboBox.h"

comboBox::comboBox(QWidget *parent) : QWidget(parent), ui(new Ui::comboBox),
    m_listWindow(NULL, Qt::Popup)
{
    ui->setupUi(this);

    m_iIndexSelected = NOSELECTED;
    m_bShowPixmap = true;

    resize(100, 20);

    connect(&m_listWindow, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));
    connect(&m_listWindow, SIGNAL(selectChanged(int)), this, SLOT(dealSelectChangedMsg(int)));
    connect(&m_listWindow, SIGNAL(selectChanged(int)), &m_listWindow, SLOT(hide()));
    connect(&m_listWindow, SIGNAL(buttonClicked(int)), &m_listWindow, SLOT(hide()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged()));

    connect(this, SIGNAL(sgn_removeItem(int)), this, SLOT(slot_removeItem(int)), Qt::QueuedConnection);
    connect(ui->pushButton_showList, SIGNAL(clicked()), this, SLOT(showListWindow()));
}

comboBox::~comboBox()
{
    delete ui;
}

void comboBox::setDefaultString(const QString &strText)
{
    ui->lineEdit->setDefaultText(strText);
}

void comboBox::setShowPixmap(bool bShow)
{
    if (m_bShowPixmap != bShow)
    {
        m_bShowPixmap = bShow;
        reSortWindow();
    }
    else
    {
        m_bShowPixmap = bShow;
    }
}

void comboBox::reSortWindow()
{
    const int iwidth = width();
    const int iHeight = height();

    ui->pushButton_showList->resize(iHeight, iHeight);
    ui->pushButton_showList->move(iwidth - iHeight, 0);
    if (m_bShowPixmap)
    {
        ui->label_showPixmap->move(4, 4);
        ui->label_showPixmap->resize(iHeight - 8, iHeight - 8);
        ui->label_showPixmap->show();

        ui->lineEdit->resize(iwidth - iHeight * 2, iHeight - 2);
        ui->lineEdit->move(iHeight, 1);
    }
    else
    {
        ui->label_showPixmap->hide();
        ui->lineEdit->resize(iwidth - iHeight, iHeight - 2);
        ui->lineEdit->move(0, 1);
    }
}

void comboBox::setCurrentIndex(int iIndex)
{
    dealSelectChangedMsg(iIndex);
}

int comboBox::currentIndex()
{
    return m_iIndexSelected;
}

QPixmap comboBox::itemPixmap(int iIndex)
{
    if (iIndex < 0 || iIndex >= m_data.size())
    {
        return QPixmap("");
    }

    return m_data[iIndex].pixmap;
}

void comboBox::removeItem(int iIndex)
{
    emit sgn_removeItem(iIndex);
}

QString comboBox::itemText(int iIndex)
{
    if (iIndex < 0 || iIndex >= m_data.size())
    {
        return "";
    }

    return m_data[iIndex].strMainText;
}

int comboBox::count()
{
    return m_data.size();
}

QString comboBox::currentText()
{
    return ui->lineEdit->text();
}

void comboBox::setEditable(bool bEditable)
{
    ui->lineEdit->setEnabled(bEditable);
}

void comboBox::setEditText(const QString &strText)
{
    ui->lineEdit->setText(strText);
}

void comboBox::setItemHeight(int iNormalHeight, int iActiveHeight)
{
    m_listWindow.setItemHeight(iNormalHeight, iActiveHeight);
}

void comboBox::setTextEditImageShow(const QPixmap &pixmap)
{
    bool bNeedReSortWindow = (ui->label_showPixmap->pixmap()->isNull() != pixmap.isNull());

    ui->label_showPixmap->setPixmap(pixmap);

    if (bNeedReSortWindow)
    {
        reSortWindow();
    }
}

void comboBox::clearEditText()
{
    ui->lineEdit->clear();
}

QVariant comboBox::itemData(int iIndex)
{
    return m_data[iIndex].data;
}

void comboBox::showListWindow()
{
    ui->lineEdit->setFocus();

    m_listWindow.setWidth(width());
    m_listWindow.setData(m_data);
    if (NULL != parentWidget())
    {
        QPoint point = parentWidget()->mapToGlobal(this->pos());
        QSize size = ui->lineEdit->size();
        point.ry() += size.height();
        m_listWindow.move(point);
    }
    m_listWindow.show();
}

void comboBox::addItem(const QString &strMainText, const QString &strMinorText, bool bNeedDelButton)
{
    comboboxData oComboboxData;

    oComboboxData.strMainText = strMainText;
    oComboboxData.strMinorText = strMinorText;
    oComboboxData.bNeedDelButton = bNeedDelButton;

    m_data.push_back(oComboboxData);

    m_listWindow.setData(m_data);
}

void comboBox::insertItem(int iIndex, const QPixmap &pixmap, const QString &strMainText,
             const QString &strMinorText, const QVariant &data, bool bNeedDelButton)
{
    comboboxData oComboboxData;

    oComboboxData.pixmap = pixmap;
    oComboboxData.strMainText = strMainText;
    oComboboxData.strMinorText = strMinorText;
    oComboboxData.bNeedDelButton = bNeedDelButton;
    oComboboxData.data = data;

    m_data.insert(iIndex, oComboboxData);

    m_listWindow.setData(m_data);
}

void comboBox::addItem(const QPixmap &pixmap, const QString &strMainText, const QString &strMinorText, bool bNeedDelButton)
{
    comboboxData oComboboxData;
    oComboboxData.pixmap = pixmap;
    oComboboxData.strMainText = strMainText;
    oComboboxData.strMinorText = strMinorText;
    oComboboxData.bNeedDelButton = bNeedDelButton;

    m_data.push_back(oComboboxData);

    m_listWindow.setData(m_data);
}

void comboBox::addItem(const QPixmap &pixmap, const QString &strMainText, const QString &strMinorText, const QVariant &data, bool bNeedDelButton)
{
    comboboxData oComboboxData;

    oComboboxData.pixmap = pixmap;
    oComboboxData.strMainText = strMainText;
    oComboboxData.strMinorText = strMinorText;
    oComboboxData.data = data;
    oComboboxData.bNeedDelButton = bNeedDelButton;

    m_data.push_back(oComboboxData);

    m_listWindow.setData(m_data);
}

void comboBox::slot_removeItem(int iIndex)
{
    if ((iIndex >= 0) && (iIndex < m_data.size()))
    {
        m_listWindow.deleteItem(iIndex);
        m_data.removeAt(iIndex);
    }

    if (iIndex == m_iIndexSelected)
    {
        if (m_data.isEmpty())
        {
            ui->lineEdit->clear();
            setCurrentIndex(-1);
        }
        else if (0 != iIndex)
        {
            setCurrentIndex(iIndex - 1);
        }
        else
        {
            setCurrentIndex(0);
        }
    }

}

void comboBox::dealSelectChangedMsg(int iIndex)
{
    if (iIndex >= m_data.size() || iIndex < 0)
    {
        ui->lineEdit->clear();
        m_iIndexSelected = -1;
    }
    else
    {
        ui->lineEdit->setText(m_data[iIndex].strMainText);
        m_iIndexSelected = iIndex;

        if (m_bShowPixmap)
        {
            ui->label_showPixmap->setPixmap(m_data[iIndex].pixmap);
        }
    }

    emit selectChanged(iIndex);
}

void comboBox::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    reSortWindow();
}

void comboBox::setItemText(int iIndex, const QString &strNewText)
{
    if (iIndex < 0 || iIndex >= m_data.size())
    {
        return;
    }

    m_data[iIndex].strMainText = strNewText;
}

void comboBox::setItemData(int iIndex, const QVariant &variant)
{
    if (iIndex < 0 || iIndex >= m_data.size())
    {
        return;
    }

    m_data[iIndex].data = variant;
}
