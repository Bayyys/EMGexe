/****************************************************************************
** Meta object code from reading C++ file 'glazer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../glazer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glazer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Glazer_t {
    QByteArrayData data[10];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Glazer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Glazer_t qt_meta_stringdata_Glazer = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Glazer"
QT_MOC_LITERAL(1, 7, 10), // "drawGlazer"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 9), // "runGlazer"
QT_MOC_LITERAL(4, 29, 15), // "dataProcessDone"
QT_MOC_LITERAL(5, 45, 8), // "maxValue"
QT_MOC_LITERAL(6, 54, 17), // "size_dataAfterRMS"
QT_MOC_LITERAL(7, 72, 16), // "QVector<double>*"
QT_MOC_LITERAL(8, 89, 12), // "dataAfterRMS"
QT_MOC_LITERAL(9, 102, 8) // "abortRun"

    },
    "Glazer\0drawGlazer\0\0runGlazer\0"
    "dataProcessDone\0maxValue\0size_dataAfterRMS\0"
    "QVector<double>*\0dataAfterRMS\0abortRun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Glazer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    3,   36,    2, 0x08 /* Private */,
       9,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Int, 0x80000000 | 7,    5,    6,    8,
    QMetaType::Void,

       0        // eod
};

void Glazer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Glazer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->drawGlazer(); break;
        case 1: _t->runGlazer(); break;
        case 2: _t->dataProcessDone((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QVector<double>*(*)>(_a[3]))); break;
        case 3: _t->abortRun(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Glazer::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Glazer.data,
    qt_meta_data_Glazer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Glazer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Glazer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Glazer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Glazer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_DataProcess_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataProcess_t qt_meta_stringdata_DataProcess = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DataProcess"
QT_MOC_LITERAL(1, 12, 11), // "resultReady"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "maxValue"
QT_MOC_LITERAL(4, 34, 17), // "size_dataAfterRMS"
QT_MOC_LITERAL(5, 52, 16), // "QVector<double>*"
QT_MOC_LITERAL(6, 69, 12), // "dataAfterRMS"
QT_MOC_LITERAL(7, 82, 10) // "runProcess"

    },
    "DataProcess\0resultReady\0\0maxValue\0"
    "size_dataAfterRMS\0QVector<double>*\0"
    "dataAfterRMS\0runProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataProcess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DataProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QVector<double>*(*)>(_a[3]))); break;
        case 1: _t->runProcess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataProcess::*)(double , int , QVector<double> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcess::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataProcess::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataProcess.data,
    qt_meta_data_DataProcess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataProcess.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DataProcess::resultReady(double _t1, int _t2, QVector<double> * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
