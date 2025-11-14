QT       += core gui network widgets charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

TARGET = CSCS
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/change_pasword_dialog.cpp \
    Sources/faileddialog.cpp \
    Sources/qcustomplot.cpp \
    Sources/usermanager.cpp \
    Sources/aboutdialog.cpp \
    Sources/adduserdialog.cpp \
    Sources/browseexperimentdialog.cpp \
    Sources/controlparamentdialog.cpp \
    Sources/logoutdialog.cpp \
    Sources/newindicattestdialog.cpp \
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
    Headers/qcustomplot.h \
    Headers/aboutdialog.h \
    Headers/adduserdialog.h \
    Headers/browseexperimentdialog.h \
    Headers/controlparamentdialog.h \
    Headers/logoutdialog.h \
    Headers/newindicattestdialog.h \
    Headers/ethercatclient.h \
    Headers/exitdialog.h \
    Headers/logindialog.h \
    Headers/mainwindow.h \
    Headers/newexperimentdialog.h \
    Headers/newfatiguetestdialog.h \
    Headers/singleapplication.h \
    Headers/systemparameterdialog.h \
    Headers/userlistdialog.h \
    Headers/usermanager.h \
    Headers/change_pasword_dialog.h \
    Headers/faileddialog.h

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
    Forms/userlistdialog.ui \
    Forms/change_pasword_dialog.ui \
    Forms/faileddialog.ui

RESOURCES += \
    Images/image.qrc \
    Themes/dark/darkstyle.qrc \
    Themes/light/lightstyle.qrc \

RC_ICONS = Images\images\CSCS.ico

QMAKE_CXXFLAGS += -fPIC
QMAKE_CXXFLAGS += -O2
QMAKE_CXXFLAGS += -mcmodel=medium

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

