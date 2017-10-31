#-------------------------------------------------
#
# Project created by QtCreator 2017-06-29T13:05:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tracing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylabel.cpp \
    spline.cpp \
    reportdialog.cpp

HEADERS  += mainwindow.h \
    mylabel.h \
    spline.h \
    reportdialog.h

FORMS    += mainwindow.ui \
    reportdialog.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += D:/opencv/build/include \
               D:/opencv/build/include/opencv \
               D:/opencv/build/include/opencv2 \

CONFIG(debug, debug|release): {
LIBS += -LD:/opencv/build/x64/vc12/lib \
-lopencv_core2413d \
-lopencv_imgproc2413d \
-lopencv_highgui2413d \
-lopencv_ml2413d \
-lopencv_video2413d \
-lopencv_features2d2413d \
-lopencv_calib3d2413d \
-lopencv_objdetect2413d \
-lopencv_contrib2413d \
-lopencv_legacy2413d \
-lopencv_flann2413d
} else:CONFIG(release, debug|release): {
LIBS += -LD:/opencv/build/x64/vc12/lib \
-lopencv_core2413 \
-lopencv_imgproc2413 \
-lopencv_highgui2413 \
-lopencv_ml2413 \
-lopencv_video2413 \
-lopencv_features2d2413 \
-lopencv_calib3d2413 \
-lopencv_objdetect2413 \
-lopencv_contrib2413 \
-lopencv_legacy2413 \
-lopencv_flann2413
}
