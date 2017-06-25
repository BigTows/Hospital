/****************************************************************************
** Meta object code from reading C++ file 'interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client/interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Interface_t {
    QByteArrayData data[16];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Interface_t qt_meta_stringdata_Interface = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Interface"
QT_MOC_LITERAL(1, 10, 12), // "onAuthResult"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 39, 5), // "reply"
QT_MOC_LITERAL(5, 45, 18), // "ongetRecordsResult"
QT_MOC_LITERAL(6, 64, 19), // "onloadPictureResult"
QT_MOC_LITERAL(7, 84, 15), // "ongetUserResult"
QT_MOC_LITERAL(8, 100, 22), // "on_EnterButton_Clicked"
QT_MOC_LITERAL(9, 123, 17), // "itemDoubleClicked"
QT_MOC_LITERAL(10, 141, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(11, 158, 4), // "item"
QT_MOC_LITERAL(12, 163, 11), // "itemClicked"
QT_MOC_LITERAL(13, 175, 17), // "calendarSelection"
QT_MOC_LITERAL(14, 193, 17), // "onbackButtonClick"
QT_MOC_LITERAL(15, 211, 14) // "onTimerTimeout"

    },
    "Interface\0onAuthResult\0\0QNetworkReply*\0"
    "reply\0ongetRecordsResult\0onloadPictureResult\0"
    "ongetUserResult\0on_EnterButton_Clicked\0"
    "itemDoubleClicked\0QListWidgetItem*\0"
    "item\0itemClicked\0calendarSelection\0"
    "onbackButtonClick\0onTimerTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Interface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       6,    1,   70,    2, 0x08 /* Private */,
       7,    1,   73,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Interface *_t = static_cast<Interface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onAuthResult((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->ongetRecordsResult((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->onloadPictureResult((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->ongetUserResult((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->on_EnterButton_Clicked(); break;
        case 5: _t->itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->calendarSelection(); break;
        case 8: _t->onbackButtonClick(); break;
        case 9: _t->onTimerTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Interface::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Interface.data,
      qt_meta_data_Interface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Interface.stringdata0))
        return static_cast<void*>(const_cast< Interface*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
