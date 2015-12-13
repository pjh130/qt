/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata[398];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 27), // "on_pushButtonSubmit_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 12), // "httpFinished"
QT_MOC_LITERAL(4, 53, 13), // "httpReadyRead"
QT_MOC_LITERAL(5, 67, 22), // "updateDataReadProgress"
QT_MOC_LITERAL(6, 90, 9), // "bytesRead"
QT_MOC_LITERAL(7, 100, 10), // "totalBytes"
QT_MOC_LITERAL(8, 111, 27), // "on_pushButtonHeader_clicked"
QT_MOC_LITERAL(9, 139, 16), // "slotCloseHeaders"
QT_MOC_LITERAL(10, 156, 7), // "strFlag"
QT_MOC_LITERAL(11, 164, 6), // "strKey"
QT_MOC_LITERAL(12, 171, 8), // "strValue"
QT_MOC_LITERAL(13, 180, 17), // "slotCloseFormdata"
QT_MOC_LITERAL(14, 198, 13), // "slotCloseXwww"
QT_MOC_LITERAL(15, 212, 23), // "slotCurrentIndexChanged"
QT_MOC_LITERAL(16, 236, 5), // "index"
QT_MOC_LITERAL(17, 242, 32), // "on_pushButtonAddFormdata_clicked"
QT_MOC_LITERAL(18, 275, 28), // "on_pushButtonAddXwww_clicked"
QT_MOC_LITERAL(19, 304, 27), // "on_pushButtonBinary_clicked"
QT_MOC_LITERAL(20, 332, 32), // "on_pushButtonCopyHeaders_clicked"
QT_MOC_LITERAL(21, 365, 32) // "on_pushButtonCopyContent_clicked"

    },
    "MainWindow\0on_pushButtonSubmit_clicked\0"
    "\0httpFinished\0httpReadyRead\0"
    "updateDataReadProgress\0bytesRead\0"
    "totalBytes\0on_pushButtonHeader_clicked\0"
    "slotCloseHeaders\0strFlag\0strKey\0"
    "strValue\0slotCloseFormdata\0slotCloseXwww\0"
    "slotCurrentIndexChanged\0index\0"
    "on_pushButtonAddFormdata_clicked\0"
    "on_pushButtonAddXwww_clicked\0"
    "on_pushButtonBinary_clicked\0"
    "on_pushButtonCopyHeaders_clicked\0"
    "on_pushButtonCopyContent_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    2,   87,    2, 0x08 /* Private */,
       8,    0,   92,    2, 0x08 /* Private */,
       9,    3,   93,    2, 0x08 /* Private */,
      13,    3,  100,    2, 0x08 /* Private */,
      14,    3,  107,    2, 0x08 /* Private */,
      15,    1,  114,    2, 0x08 /* Private */,
      17,    0,  117,    2, 0x08 /* Private */,
      18,    0,  118,    2, 0x08 /* Private */,
      19,    0,  119,    2, 0x08 /* Private */,
      20,    0,  120,    2, 0x08 /* Private */,
      21,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pushButtonSubmit_clicked(); break;
        case 1: _t->httpFinished(); break;
        case 2: _t->httpReadyRead(); break;
        case 3: _t->updateDataReadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->on_pushButtonHeader_clicked(); break;
        case 5: _t->slotCloseHeaders((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: _t->slotCloseFormdata((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->slotCloseXwww((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 8: _t->slotCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_pushButtonAddFormdata_clicked(); break;
        case 10: _t->on_pushButtonAddXwww_clicked(); break;
        case 11: _t->on_pushButtonBinary_clicked(); break;
        case 12: _t->on_pushButtonCopyHeaders_clicked(); break;
        case 13: _t->on_pushButtonCopyContent_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
