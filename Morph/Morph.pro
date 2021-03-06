#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T23:08:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Morph
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    widget.cpp \
    pointbutton.cpp \
    mesh.cpp \
    main_component.cpp \
    image_util.cpp \
    image_seperator.cpp \
    image_morph.cpp \
    image_meshwarp.cpp \
    image_merger.cpp \
    image_io_processor.cpp \
    catmullrom.cpp \
    meshtabwidget.cpp \
    image_portrait_processor.cpp \
    settingwidget.cpp \
    imagesettingwidget.cpp \
    pointsettingwidget.cpp

HEADERS += \
        mainwindow.h \
    widget.h \
    pointbutton.h \
    mesh.h \
    typedef_cxx.h \
    main_component.h \
    image_util.h \
    image_seperator.h \
    image_morph.h \
    image_meshwarp.h \
    image_merger.h \
    image_io_processor.h \
    catmullrom.h \
    meshtabwidget.h \
    image_portrait_processor.h \
    settingwidget.h \
    imagesettingwidget.h \
    pointsettingwidget.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib \
 -lcblas\
 -lclapack\
 -ldlib\
 -lopencv_stitching \
 -lopencv_superres \
 -lopencv_videostab \
 -lopencv_shape \
 -lopencv_video \
 -lopencv_calib3d \
 -lopencv_features2d \
 -lopencv_flann \
 -lopencv_objdetect \
 -lopencv_ml \
 -lopencv_highgui \
 -lopencv_videoio \
 -lopencv_imgcodecs \
 -lopencv_photo \
 -lopencv_imgproc \
 -lopencv_core
