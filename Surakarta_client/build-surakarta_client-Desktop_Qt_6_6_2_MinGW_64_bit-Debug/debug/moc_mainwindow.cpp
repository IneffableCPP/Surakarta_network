/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../surakarta_client/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "chessOneByPerson",
    "",
    "chessOneByAi",
    "initPVPGame",
    "initPVCGame",
    "playagain",
    "admitlose",
    "whitewin",
    "blackwin",
    "nonewin",
    "updateTurn",
    "updatePlayer",
    "updateDdl",
    "receive",
    "displayError",
    "connected"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[34];
    char stringdata0[11];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[12];
    char stringdata5[12];
    char stringdata6[10];
    char stringdata7[10];
    char stringdata8[9];
    char stringdata9[9];
    char stringdata10[8];
    char stringdata11[11];
    char stringdata12[13];
    char stringdata13[10];
    char stringdata14[8];
    char stringdata15[13];
    char stringdata16[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 16),  // "chessOneByPerson"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 12),  // "chessOneByAi"
        QT_MOC_LITERAL(42, 11),  // "initPVPGame"
        QT_MOC_LITERAL(54, 11),  // "initPVCGame"
        QT_MOC_LITERAL(66, 9),  // "playagain"
        QT_MOC_LITERAL(76, 9),  // "admitlose"
        QT_MOC_LITERAL(86, 8),  // "whitewin"
        QT_MOC_LITERAL(95, 8),  // "blackwin"
        QT_MOC_LITERAL(104, 7),  // "nonewin"
        QT_MOC_LITERAL(112, 10),  // "updateTurn"
        QT_MOC_LITERAL(123, 12),  // "updatePlayer"
        QT_MOC_LITERAL(136, 9),  // "updateDdl"
        QT_MOC_LITERAL(146, 7),  // "receive"
        QT_MOC_LITERAL(154, 12),  // "displayError"
        QT_MOC_LITERAL(167, 9)   // "connected"
    },
    "MainWindow",
    "chessOneByPerson",
    "",
    "chessOneByAi",
    "initPVPGame",
    "initPVCGame",
    "playagain",
    "admitlose",
    "whitewin",
    "blackwin",
    "nonewin",
    "updateTurn",
    "updatePlayer",
    "updateDdl",
    "receive",
    "displayError",
    "connected"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    0,  105,    2, 0x08,    2 /* Private */,
       4,    0,  106,    2, 0x08,    3 /* Private */,
       5,    0,  107,    2, 0x08,    4 /* Private */,
       6,    0,  108,    2, 0x08,    5 /* Private */,
       7,    0,  109,    2, 0x08,    6 /* Private */,
       8,    0,  110,    2, 0x08,    7 /* Private */,
       9,    0,  111,    2, 0x08,    8 /* Private */,
      10,    0,  112,    2, 0x08,    9 /* Private */,
      11,    0,  113,    2, 0x08,   10 /* Private */,
      12,    0,  114,    2, 0x08,   11 /* Private */,
      13,    0,  115,    2, 0x08,   12 /* Private */,
      14,    0,  116,    2, 0x08,   13 /* Private */,
      15,    0,  117,    2, 0x08,   14 /* Private */,
      16,    0,  118,    2, 0x08,   15 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'chessOneByPerson'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'chessOneByAi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initPVPGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initPVCGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playagain'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'admitlose'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'whitewin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'blackwin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nonewin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTurn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatePlayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateDdl'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->chessOneByPerson(); break;
        case 1: _t->chessOneByAi(); break;
        case 2: _t->initPVPGame(); break;
        case 3: _t->initPVCGame(); break;
        case 4: _t->playagain(); break;
        case 5: _t->admitlose(); break;
        case 6: _t->whitewin(); break;
        case 7: _t->blackwin(); break;
        case 8: _t->nonewin(); break;
        case 9: _t->updateTurn(); break;
        case 10: _t->updatePlayer(); break;
        case 11: _t->updateDdl(); break;
        case 12: _t->receive(); break;
        case 13: _t->displayError(); break;
        case 14: _t->connected(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
