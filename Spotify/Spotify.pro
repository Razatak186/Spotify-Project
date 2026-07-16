QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    album.cpp \
    albumrepository.cpp \
    appcontroller.cpp \
    artistcontroller.cpp \
    artistrepository.cpp \
    listenercontroller.cpp \
    listenerrepository.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    playlist.cpp \
    playlistrepository.cpp \
    registerwindow.cpp \
    song.cpp \
    songrepository.cpp \
    sorthelper.cpp

HEADERS += \
    abstractrepository.h \
    account.h \
    accountrepository.h \
    album.h \
    albumrepository.h \
    appcontroller.h \
    artistcontroller.h \
    artistrepository.h \
    listenercontroller.h \
    listenerrepository.h \
    loginwindow.h \
    mainwindow.h \
    playlist.h \
    playlistrepository.h \
    registerwindow.h \
    song.h \
    songrepository.h \
    sorthelper.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
