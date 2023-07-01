/****************************************************************************
** Meta object code from reading C++ file 'connect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../connect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CommnicateBoard_t {
    QByteArrayData data[14];
    char stringdata0[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CommnicateBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CommnicateBoard_t qt_meta_stringdata_CommnicateBoard = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CommnicateBoard"
QT_MOC_LITERAL(1, 16, 18), // "signal_board_start"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "signal_tcp_abort"
QT_MOC_LITERAL(4, 53, 24), // "signal_start_decode_data"
QT_MOC_LITERAL(5, 78, 36), // "slot_wifi_tcp_client_connect_..."
QT_MOC_LITERAL(6, 115, 35), // "slot_wifi_tcp_client_connect_..."
QT_MOC_LITERAL(7, 151, 30), // "slot_wifi_tcp_client_find_host"
QT_MOC_LITERAL(8, 182, 30), // "slot_wifi_tcp_client_read_data"
QT_MOC_LITERAL(9, 213, 32), // "slot_wifi_tcp_server_new_connect"
QT_MOC_LITERAL(10, 246, 30), // "slot_wifi_server_connect_error"
QT_MOC_LITERAL(11, 277, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(12, 306, 14), // "slot_read_data"
QT_MOC_LITERAL(13, 321, 18) // "slot_set_debug_off"

    },
    "CommnicateBoard\0signal_board_start\0\0"
    "signal_tcp_abort\0signal_start_decode_data\0"
    "slot_wifi_tcp_client_connect_success\0"
    "slot_wifi_tcp_client_connect_failed\0"
    "slot_wifi_tcp_client_find_host\0"
    "slot_wifi_tcp_client_read_data\0"
    "slot_wifi_tcp_server_new_connect\0"
    "slot_wifi_server_connect_error\0"
    "QAbstractSocket::SocketError\0"
    "slot_read_data\0slot_set_debug_off"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CommnicateBoard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      12,    0,   80,    2, 0x08 /* Private */,
      13,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CommnicateBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommnicateBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_board_start(); break;
        case 1: _t->signal_tcp_abort(); break;
        case 2: _t->signal_start_decode_data(); break;
        case 3: _t->slot_wifi_tcp_client_connect_success(); break;
        case 4: _t->slot_wifi_tcp_client_connect_failed(); break;
        case 5: _t->slot_wifi_tcp_client_find_host(); break;
        case 6: _t->slot_wifi_tcp_client_read_data(); break;
        case 7: _t->slot_wifi_tcp_server_new_connect(); break;
        case 8: _t->slot_wifi_server_connect_error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 9: _t->slot_read_data(); break;
        case 10: _t->slot_set_debug_off(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CommnicateBoard::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommnicateBoard::signal_board_start)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CommnicateBoard::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommnicateBoard::signal_tcp_abort)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CommnicateBoard::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommnicateBoard::signal_start_decode_data)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CommnicateBoard::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_CommnicateBoard.data,
    qt_meta_data_CommnicateBoard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CommnicateBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommnicateBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CommnicateBoard.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CommnicateBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void CommnicateBoard::signal_board_start()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CommnicateBoard::signal_tcp_abort()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CommnicateBoard::signal_start_decode_data()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_DebugShow_t {
    QByteArrayData data[5];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DebugShow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DebugShow_t qt_meta_stringdata_DebugShow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DebugShow"
QT_MOC_LITERAL(1, 10, 16), // "signal_need_exit"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "run"
QT_MOC_LITERAL(4, 32, 16) // "slot_exit_widget"

    },
    "DebugShow\0signal_need_exit\0\0run\0"
    "slot_exit_widget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DebugShow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DebugShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DebugShow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_need_exit(); break;
        case 1: _t->run(); break;
        case 2: _t->slot_exit_widget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DebugShow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DebugShow::signal_need_exit)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DebugShow::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DebugShow.data,
    qt_meta_data_DebugShow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DebugShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DebugShow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DebugShow.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DebugShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DebugShow::signal_need_exit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_Decode_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Decode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Decode_t qt_meta_stringdata_Decode = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Decode"
QT_MOC_LITERAL(1, 7, 22), // "slot_start_decode_data"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "Decode\0slot_start_decode_data\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Decode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Decode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Decode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_start_decode_data(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Decode::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Decode.data,
    qt_meta_data_Decode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Decode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Decode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Decode.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Decode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_ReadSavedFile_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReadSavedFile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReadSavedFile_t qt_meta_stringdata_ReadSavedFile = {
    {
QT_MOC_LITERAL(0, 0, 13) // "ReadSavedFile"

    },
    "ReadSavedFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReadSavedFile[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ReadSavedFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ReadSavedFile::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_ReadSavedFile.data,
    qt_meta_data_ReadSavedFile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ReadSavedFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReadSavedFile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReadSavedFile.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ReadSavedFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
