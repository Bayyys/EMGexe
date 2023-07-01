/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../login.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_login_t {
    QByteArrayData data[12];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_login_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_login_t qt_meta_stringdata_login = {
    {
QT_MOC_LITERAL(0, 0, 5), // "login"
QT_MOC_LITERAL(1, 6, 15), // "on_eval_clicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "reshow"
QT_MOC_LITERAL(4, 30, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(5, 54, 27), // "on_action_connect_triggered"
QT_MOC_LITERAL(6, 82, 29), // "on_action_reconnect_triggered"
QT_MOC_LITERAL(7, 112, 4), // "send"
QT_MOC_LITERAL(8, 117, 5), // "char*"
QT_MOC_LITERAL(9, 123, 4), // "data"
QT_MOC_LITERAL(10, 128, 28), // "on_action_linktest_triggered"
QT_MOC_LITERAL(11, 157, 30) // "on_action_reporttest_triggered"

    },
    "login\0on_eval_clicked\0\0reshow\0"
    "on_pushButton_2_clicked\0"
    "on_action_connect_triggered\0"
    "on_action_reconnect_triggered\0send\0"
    "char*\0data\0on_action_linktest_triggered\0"
    "on_action_reporttest_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_login[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    0,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void login::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<login *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_eval_clicked(); break;
        case 1: _t->reshow(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_action_connect_triggered(); break;
        case 4: _t->on_action_reconnect_triggered(); break;
        case 5: _t->send((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 6: _t->on_action_linktest_triggered(); break;
        case 7: _t->on_action_reporttest_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject login::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_login.data,
    qt_meta_data_login,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *login::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_login.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
