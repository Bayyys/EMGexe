/****************************************************************************
** Meta object code from reading C++ file 'glazer_analyse.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../class/glazer_analyse.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glazer_analyse.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Glazer_analyse_t {
    QByteArrayData data[4];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Glazer_analyse_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Glazer_analyse_t qt_meta_stringdata_Glazer_analyse = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Glazer_analyse"
QT_MOC_LITERAL(1, 15, 11), // "glazer_done"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11) // "mid_stopped"

    },
    "Glazer_analyse\0glazer_done\0\0mid_stopped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Glazer_analyse[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Glazer_analyse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Glazer_analyse *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->glazer_done(); break;
        case 1: _t->mid_stopped(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Glazer_analyse::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Glazer_analyse::glazer_done)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Glazer_analyse::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Glazer_analyse::mid_stopped)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Glazer_analyse::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_Glazer_analyse.data,
    qt_meta_data_Glazer_analyse,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Glazer_analyse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Glazer_analyse::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Glazer_analyse.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Glazer_analyse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void Glazer_analyse::glazer_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Glazer_analyse::mid_stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
