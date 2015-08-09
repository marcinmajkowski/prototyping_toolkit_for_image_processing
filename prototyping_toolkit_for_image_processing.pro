#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T01:19:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prototyping_toolkit_for_image_processing
TEMPLATE = app

include(Filters/Filters.pri)
include(Filters/Arguments/Arguments.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    codewidget.cpp \
    filterswidget.cpp \
    imagewidget.cpp \
    pipelinewidget.cpp \
    pipelinewidgetitem.cpp

HEADERS  += mainwindow.h \
    codewidget.h \
    filterswidget.h \
    imagewidget.h \
    asmOpenCV.h \
    pipelinewidget.h \
    pipelinewidgetitem.h

win32 {
    INCLUDEPATH += "D:\\OpenCV2.4.9\\build\\include" \

    CONFIG(debug,debug|release) {
        LIBS += -L"D:\\OpenCV2.4.9\\build\\x64\\vc12\\lib" \
            -lopencv_core249d \
            -lopencv_highgui249d \
            -lopencv_imgproc249d \
#            -lopencv_features2d249d \
#            -lopencv_calib3d249d
    }

    CONFIG(release,debug|release) {
        DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
        LIBS += -L"D:\\OpenCV2.4.9\\build\\x64\\vc12\\lib" \
            -lopencv_core249 \
            -lopencv_highgui249 \
            -lopencv_imgproc249 \
#            -lopencv_features2d249 \
#            -lopencv_calib3d249
    }
}


unix {
    QT_CONFIG -= no-pkg-config
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    QMAKE_CXXFLAGS += -std=c++1y
    QMAKE_CXXFLAGS += -Wall
#    INCLUDEPATH += /usr/local/include/opencv
#    LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui
}

RESOURCES += \
    images.qrc
