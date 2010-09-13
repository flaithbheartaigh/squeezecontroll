/****************************************************************************
** Meta object code from reading C++ file 'kineticlist.h'
**
** Created: Fri 19. Mar 14:07:31 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kineticlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kineticlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_kineticList[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      30,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_kineticList[] = {
    "kineticList\0\0doubleClick(int)\0"
    "endOfScroll(int)\0"
};

const QMetaObject kineticList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_kineticList,
      qt_meta_data_kineticList, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &kineticList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *kineticList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *kineticList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_kineticList))
        return static_cast<void*>(const_cast< kineticList*>(this));
    if (!strcmp(_clname, "Flickable"))
        return static_cast< Flickable*>(const_cast< kineticList*>(this));
    return QWidget::qt_metacast(_clname);
}

int kineticList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: doubleClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: endOfScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void kineticList::doubleClick(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void kineticList::endOfScroll(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
