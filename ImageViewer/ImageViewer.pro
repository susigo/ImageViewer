QT += gui widgets core

TEMPLATE = lib
DEFINES += IMAGEVIEWER_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = lib

SOURCES += \
    ImageViewWidget.cpp \
    ImageViewer.cpp \
    ShapeBase.cpp \
    ShapeHandle.cpp

HEADERS += \
    ImageViewWidget.h \
    ImageViewer_global.h \
    ImageViewer.h \
    ShapeBase.h \
    ShapeHandle.h

CONFIG(debug, debug|release){
    DESTDIR =../Build/Debug/
}else{
    DESTDIR =../Build/Release/
}

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ImageViewWidget.ui

RESOURCES += \
    icons.qrc
