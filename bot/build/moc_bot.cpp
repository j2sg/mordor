/****************************************************************************
** Meta object code from reading C++ file 'bot.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/bot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Bot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x08,
      25,   17,    4,    4, 0x08,
      61,   55,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Bot[] = {
    "Bot\0\0connected()\0message\0"
    "messageReceived(QXmppMessage)\0error\0"
    "error(QXmppClient::Error)\0"
};

void Bot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Bot *_t = static_cast<Bot *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->messageReceived((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        case 2: _t->error((*reinterpret_cast< QXmppClient::Error(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Bot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Bot::staticMetaObject = {
    { &QXmppClient::staticMetaObject, qt_meta_stringdata_Bot,
      qt_meta_data_Bot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Bot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Bot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Bot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Bot))
        return static_cast<void*>(const_cast< Bot*>(this));
    return QXmppClient::qt_metacast(_clname);
}

int Bot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QXmppClient::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
