QT       += core gui network widgets charts sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

TARGET = CSCS
TEMPLATE = app

# DESTDIR = $$_PRO_FILE_PWD_/Bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # Sources/plcmanager.cpp \
    Sources/log.cpp \
    Sources/change_pasword_dialog.cpp \
    Sources/faileddialog.cpp \
    Sources/logmanager.cpp \
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
    # Headers/plcmanager.h \
    Headers/log.h \
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
    Headers/faileddialog.h \
    Headers/logmanager.h

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
    Themes/light/lightstyle.qrc

RC_ICONS = Images\images\CSCS.ico

QMAKE_CXXFLAGS += -fPIC
QMAKE_CXXFLAGS += -O2
QMAKE_CXXFLAGS += -mcmodel=medium

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# # 添加库的头文件路径
# INCLUDEPATH += $$PWD/Include  # 指向 Library 的头文件路径

# # 链接库文件
# LIBS += $$PWD/Library/libHMIKernel.a  # -lMyLibrary 会链接 libMyLibrary.so 或 MyLibrary.dll

TRANSLATIONS += \
    Translations/newsoft_en_001.ts \
    Translations/newsoft_zh_CN.ts

TS_DIR = Translations/

# ==== 头文件路径 ====
INCLUDEPATH += $$PWD/HMIKernel/include

# ==== 库文件路径 ====
LIBS += -L$$PWD/HMIKernel/lib

# ==== 链接库 ====
LIBS += -lHMIKernel

#复制Database文件到build文件下
# 复制数据库文件到构建目录
database_files.path = $$OUT_PWD/debug/Database
database_files.files += Database/user/user.db
database_files.files += Database/log/log.db

# 确保在构建后执行复制
COPIES += database_files

bin_files.path = $$OUT_PWD/debug/Data
bin_files.files += $$PWD/Bin/Data
COPIES += bin_files

# translation_files.path = $$OUT_PWD/debug/Translations
# translation_files.files += Translations/res/newsoft_en_001.qm
# translation_files.files += Translations/res/newsoft_zh_CN.qm

# 确保在构建后执行复制
COPIES += translation_files

lib_files.path = $$OUT_PWD/debug/
lib_files.files += HMIKernel/lib/HMIKernel.dll
lib_files.files += Bin/comm.config
lib_files.files += Bin/config.ini
lib_files.files += Bin/configCurve.ini
lib_files.files += Bin/HMI_DB.db
lib_files.files += Bin/MoldIDList.xml

# 确保在构建后执行复制
COPIES += lib_files
