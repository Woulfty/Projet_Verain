/****************************************************************************
** Meta object code from reading C++ file 'PosteBanc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../PosteBanc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PosteBanc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PosteBanc_t {
    QByteArrayData data[15];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PosteBanc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PosteBanc_t qt_meta_stringdata_PosteBanc = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PosteBanc"
QT_MOC_LITERAL(1, 10, 14), // "ConnectServeur"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 17), // "onSocketConnected"
QT_MOC_LITERAL(4, 44, 19), // "onSocketDeconnected"
QT_MOC_LITERAL(5, 64, 17), // "onSocketReadyRead"
QT_MOC_LITERAL(6, 82, 14), // "ChangeValueIHM"
QT_MOC_LITERAL(7, 97, 17), // "EnableChangeValue"
QT_MOC_LITERAL(8, 115, 18), // "ChangeValueAffaire"
QT_MOC_LITERAL(9, 134, 13), // "DeleteAffaire"
QT_MOC_LITERAL(10, 148, 9), // "StartRead"
QT_MOC_LITERAL(11, 158, 6), // "Mesure"
QT_MOC_LITERAL(12, 165, 8), // "SendData"
QT_MOC_LITERAL(13, 174, 9), // "StopTimer"
QT_MOC_LITERAL(14, 184, 11) // "CreateGraph"

    },
    "PosteBanc\0ConnectServeur\0\0onSocketConnected\0"
    "onSocketDeconnected\0onSocketReadyRead\0"
    "ChangeValueIHM\0EnableChangeValue\0"
    "ChangeValueAffaire\0DeleteAffaire\0"
    "StartRead\0Mesure\0SendData\0StopTimer\0"
    "CreateGraph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PosteBanc[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    1,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void PosteBanc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PosteBanc *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ConnectServeur(); break;
        case 1: _t->onSocketConnected(); break;
        case 2: _t->onSocketDeconnected(); break;
        case 3: _t->onSocketReadyRead(); break;
        case 4: _t->ChangeValueIHM(); break;
        case 5: _t->EnableChangeValue(); break;
        case 6: _t->ChangeValueAffaire(); break;
        case 7: _t->DeleteAffaire(); break;
        case 8: _t->StartRead(); break;
        case 9: _t->Mesure(); break;
        case 10: _t->SendData(); break;
        case 11: _t->StopTimer(); break;
        case 12: _t->CreateGraph((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PosteBanc::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_PosteBanc.data,
    qt_meta_data_PosteBanc,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PosteBanc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PosteBanc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PosteBanc.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PosteBanc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
