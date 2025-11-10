QT       += core gui network widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

TARGET = CSCS
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    adduserdialog.cpp \
    browseexperimentdialog.cpp \
    controlparamentdialog.cpp \
    logoutdialog.cpp \
    newindicattestdialog.cpp \
    qcustomplot.cpp \
    ethercatclient.cpp \
    exitdialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    newexperimentdialog.cpp \
    newfatiguetestdialog.cpp \
    singleapplication.cpp \
    systemparameterdialog.cpp \
    userlistdialog.cpp

HEADERS += \
    aboutdialog.h \
    adduserdialog.h \
    browseexperimentdialog.h \
    controlparamentdialog.h \
    logoutdialog.h \
    newindicattestdialog.h \
    qcustomplot.h \
    ethercatclient.h \
    exitdialog.h \
    logindialog.h \
    mainwindow.h \
    newexperimentdialog.h \
    newfatiguetestdialog.h \
    singleapplication.h \
    systemparameterdialog.h \
    userlistdialog.h

FORMS += \
    aboutdialog.ui \
    adduserdialog.ui \
    browseexperimentdialog.ui \
    controlparamentdialog.ui \
    exitdialog.ui \
    logindialog.ui \
    logoutdialog.ui \
    mainwindow.ui \
    newexperimentdialog.ui \
    newfatiguetestdialog.ui \
    newindicattestdialog.ui \
    systemparameterdialog.ui \
    userlistdialog.ui

RESOURCES += \
    themes/dark/darkstyle.qrc \
    themes/image.qrc \
    themes/light/lightstyle.qrc

RC_ICONS = themes\images\CSCS.ico

QMAKE_CXXFLAGS += -fPIC
QMAKE_CXXFLAGS += -O2
QMAKE_CXXFLAGS += -mcmodel=medium

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

