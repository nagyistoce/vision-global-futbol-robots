/****************************************************************************
** Meta object code from reading C++ file 'editcamgui.h'
**
** Created: Mon Oct 17 23:28:10 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editcamgui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editcamgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_editCamGUI[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x09,
      33,   11,   11,   11, 0x09,
      47,   11,   11,   11, 0x09,
      60,   11,   11,   11, 0x09,
      79,   11,   11,   11, 0x09,
      98,   11,   11,   11, 0x09,
     112,   11,   11,   11, 0x09,
     126,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_editCamGUI[] = {
    "editCamGUI\0\0spinBoxCamaraIndex()\0"
    "buttonStart()\0buttonStop()\0"
    "buttonIntrinsics()\0buttonDistortion()\0"
    "buttonApply()\0buttonClear()\0"
    "buttonConfiguration()\0"
};

const QMetaObject editCamGUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_editCamGUI,
      qt_meta_data_editCamGUI, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &editCamGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *editCamGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *editCamGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_editCamGUI))
        return static_cast<void*>(const_cast< editCamGUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int editCamGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: spinBoxCamaraIndex(); break;
        case 1: buttonStart(); break;
        case 2: buttonStop(); break;
        case 3: buttonIntrinsics(); break;
        case 4: buttonDistortion(); break;
        case 5: buttonApply(); break;
        case 6: buttonClear(); break;
        case 7: buttonConfiguration(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
