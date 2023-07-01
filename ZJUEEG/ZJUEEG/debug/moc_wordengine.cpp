/****************************************************************************
** Meta object code from reading C++ file 'wordengine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../wordengine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wordengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WordEngine_t {
    QByteArrayData data[15];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WordEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WordEngine_t qt_meta_stringdata_WordEngine = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WordEngine"
QT_MOC_LITERAL(1, 11, 4), // "open"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 4), // "file"
QT_MOC_LITERAL(4, 22, 4), // "save"
QT_MOC_LITERAL(5, 27, 8), // "savePath"
QT_MOC_LITERAL(6, 36, 11), // "replaceText"
QT_MOC_LITERAL(7, 48, 5), // "label"
QT_MOC_LITERAL(8, 54, 4), // "text"
QT_MOC_LITERAL(9, 59, 18), // "alterTableRowCount"
QT_MOC_LITERAL(10, 78, 5), // "tabel"
QT_MOC_LITERAL(11, 84, 8), // "rowCount"
QT_MOC_LITERAL(12, 93, 13), // "fillTableCell"
QT_MOC_LITERAL(13, 107, 18), // "QList<QStringList>"
QT_MOC_LITERAL(14, 126, 4) // "data"

    },
    "WordEngine\0open\0\0file\0save\0savePath\0"
    "replaceText\0label\0text\0alterTableRowCount\0"
    "tabel\0rowCount\0fillTableCell\0"
    "QList<QStringList>\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WordEngine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       6,    2,   45,    2, 0x0a /* Public */,
       9,    2,   50,    2, 0x0a /* Public */,
      12,    2,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13,   10,   14,

       0        // eod
};

void WordEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WordEngine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->save((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->replaceText((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->alterTableRowCount((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->fillTableCell((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QList<QStringList>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QStringList> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WordEngine::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WordEngine.data,
    qt_meta_data_WordEngine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WordEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WordEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WordEngine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WordEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
