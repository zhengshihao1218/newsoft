QT       += core gui network widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

TARGET = CSCS
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/aboutdialog.cpp \
    Sources/adduserdialog.cpp \
    Sources/browseexperimentdialog.cpp \
    Sources/controlparamentdialog.cpp \
    Sources/logoutdialog.cpp \
    Sources/newindicattestdialog.cpp \
    Sources/qcustomplot.cpp \
    Sources/ethercatclient.cpp \
    Sources/exitdialog.cpp \
    Sources/logindialog.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/newexperimentdialog.cpp \
    Sources/newfatiguetestdialog.cpp \
    Sources/singleapplication.cpp \
    Sources/systemparameterdialog.cpp \
    Sources/userlistdialog.cpp

HEADERS += \
    Headers/aboutdialog.h \
    Headers/adduserdialog.h \
    Headers/browseexperimentdialog.h \
    Headers/controlparamentdialog.h \
    Headers/logoutdialog.h \
    Headers/newindicattestdialog.h \
    Headers/qcustomplot.h \
    Headers/ethercatclient.h \
    Headers/exitdialog.h \
    Headers/logindialog.h \
    Headers/mainwindow.h \
    Headers/newexperimentdialog.h \
    Headers/newfatiguetestdialog.h \
    Headers/singleapplication.h \
    Headers/systemparameterdialog.h \
    Headers/userlistdialog.h

FORMS += \
    Forms/aboutdialog.ui \
    Forms/adduserdialog.ui \
    Forms/browseexperimentdialog.ui \
    Forms/controlparamentdialog.ui \
    Forms/exitdialog.ui \
    Forms/logindialog.ui \
    Forms/logoutdialog.ui \
    Forms/mainwindow.ui \
    Forms/newexperimentdialog.ui \
    Forms/newfatiguetestdialog.ui \
    Forms/newindicattestdialog.ui \
    Forms/systemparameterdialog.ui \
    Forms/userlistdialog.ui

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

