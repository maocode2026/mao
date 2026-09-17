QT += widgets
QT += sql
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mydatabase.cpp \
    userinfo.cpp

HEADERS += \
    logindialog.h \
    mainwindow.h \
    mydatabase.h \
    userinfo.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# 指定opencv头文件所在路径
INCLUDEPATH += D:/opencv4.5.5-MinGw7.3.0/include

# 指定opencv库文件路径及库名称
LIBS += -LD:/opencv4.5.5-MinGw7.3.0/x64/mingw/bin -lopencv_world455

