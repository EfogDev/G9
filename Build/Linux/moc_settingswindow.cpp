/****************************************************************************
** Meta object code from reading C++ file 'settingswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Source/settingswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Label_t {
    QByteArrayData data[3];
    char stringdata[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Label_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Label_t qt_meta_stringdata_Label = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Label"
QT_MOC_LITERAL(1, 6, 7), // "clicked"
QT_MOC_LITERAL(2, 14, 0) // ""

    },
    "Label\0clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Label[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void Label::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Label *_t = static_cast<Label *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Label::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Label::clicked)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Label::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_Label.data,
      qt_meta_data_Label,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Label::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Label::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Label.stringdata))
        return static_cast<void*>(const_cast< Label*>(this));
    return QLabel::qt_metacast(_clname);
}

int Label::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Label::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_SettingsWindow_t {
    QByteArrayData data[16];
    char stringdata[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsWindow_t qt_meta_stringdata_SettingsWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SettingsWindow"
QT_MOC_LITERAL(1, 15, 5), // "saved"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "Settings"
QT_MOC_LITERAL(4, 31, 8), // "settings"
QT_MOC_LITERAL(5, 40, 15), // "autoSaveChanged"
QT_MOC_LITERAL(6, 56, 20), // "autoSaveLabelClicked"
QT_MOC_LITERAL(7, 77, 20), // "autoCopyLabelClicked"
QT_MOC_LITERAL(8, 98, 17), // "soundLabelClicked"
QT_MOC_LITERAL(9, 116, 26), // "activeGrabbingLabelClicked"
QT_MOC_LITERAL(10, 143, 26), // "saveFormatComboBoxSelected"
QT_MOC_LITERAL(11, 170, 5), // "index"
QT_MOC_LITERAL(12, 176, 20), // "saveDirButtonClicked"
QT_MOC_LITERAL(13, 197, 23), // "frameColorButtonClicked"
QT_MOC_LITERAL(14, 221, 11), // "saveClicked"
QT_MOC_LITERAL(15, 233, 13) // "cancelClicked"

    },
    "SettingsWindow\0saved\0\0Settings\0settings\0"
    "autoSaveChanged\0autoSaveLabelClicked\0"
    "autoCopyLabelClicked\0soundLabelClicked\0"
    "activeGrabbingLabelClicked\0"
    "saveFormatComboBoxSelected\0index\0"
    "saveDirButtonClicked\0frameColorButtonClicked\0"
    "saveClicked\0cancelClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      12,    0,   80,    2, 0x08 /* Private */,
      13,    0,   81,    2, 0x08 /* Private */,
      14,    0,   82,    2, 0x08 /* Private */,
      15,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingsWindow *_t = static_cast<SettingsWindow *>(_o);
        switch (_id) {
        case 0: _t->saved((*reinterpret_cast< Settings(*)>(_a[1]))); break;
        case 1: _t->autoSaveChanged(); break;
        case 2: _t->autoSaveLabelClicked(); break;
        case 3: _t->autoCopyLabelClicked(); break;
        case 4: _t->soundLabelClicked(); break;
        case 5: _t->activeGrabbingLabelClicked(); break;
        case 6: _t->saveFormatComboBoxSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->saveDirButtonClicked(); break;
        case 8: _t->frameColorButtonClicked(); break;
        case 9: _t->saveClicked(); break;
        case 10: _t->cancelClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SettingsWindow::*_t)(Settings );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsWindow::saved)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SettingsWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SettingsWindow.data,
      qt_meta_data_SettingsWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SettingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsWindow.stringdata))
        return static_cast<void*>(const_cast< SettingsWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int SettingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SettingsWindow::saved(Settings _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
