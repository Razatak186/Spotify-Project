QT += widgets
QT += widgets multimedia

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    addalbumdialog.cpp \
    addplaylistdialog.cpp \
    addsongdialog.cpp \
    album.cpp \
    albumrepository.cpp \
    appcontroller.cpp \
    artistcontroller.cpp \
    artistrepository.cpp \
    artistwindow.cpp \
    editalbumdialog.cpp \
    editplaylistdialog.cpp \
    editprofiledialog.cpp \
    editsongdialog.cpp \
    listenercontroller.cpp \
    listenerrepository.cpp \
    listenerwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    playbackmanager.cpp \
    playlist.cpp \
    playlistrepository.cpp \
    registerwindow.cpp \
    selectplaylistdialog.cpp \
    song.cpp \
    songrepository.cpp \
    sorthelper.cpp

HEADERS += \
    abstractrepository.h \
    account.h \
    accountrepository.h \
    addalbumdialog.h \
    addplaylistdialog.h \
    addsongdialog.h \
    album.h \
    albumrepository.h \
    appcontroller.h \
    artistcontroller.h \
    artistrepository.h \
    artistwindow.h \
    editalbumdialog.h \
    editplaylistdialog.h \
    editprofiledialog.h \
    editsongdialog.h \
    listenercontroller.h \
    listenerrepository.h \
    listenerwindow.h \
    loginwindow.h \
    mainwindow.h \
    playbackmanager.h \
    playlist.h \
    playlistrepository.h \
    registerwindow.h \
    selectplaylistdialog.h \
    song.h \
    songrepository.h \
    sorthelper.h

FORMS += \
    addalbumdialog.ui \
    addplaylistdialog.ui \
    addsongdialog.ui \
    artistwindow.ui \
    editalbumdialog.ui \
    editplaylistdialog.ui \
    editprofiledialog.ui \
    editsongdialog.ui \
    listenerwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    registerwindow.ui \
    selectplaylistdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
