#-------------------------------------------------
#
# Project created by QtCreator 2018-12-08T17:50:08
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += core gui printsupport
QT       += serialport
QT       += widgets gui axcontainer
QT       += multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZJUEEG
TEMPLATE = app


SOURCES += main.cpp\
    class/glazer_analyse.cpp \
    connect.cpp \
    debugwidget.cpp \
        mainwindow.cpp \
    myframe.cpp \
    signalprocess.cpp \
    glazer.cpp \
    qcustomplot/qcustomplot.cpp \
    iir/Biquad.cpp \
    iir/Butterworth.cpp \
    iir/Cascade.cpp \
    iir/ChebyshevI.cpp \
    iir/ChebyshevII.cpp \
    iir/Custom.cpp \
    iir/PoleFilter.cpp \
    iir/RBJ.cpp \
    iir/State.cpp \
    FFT/FFT.cpp \
    FFT/fft2.cpp \
    FFT/FFT_emxAPI.cpp \
    FFT/FFT_emxutil.cpp \
    FFT/FFT_initialize.cpp \
    FFT/FFT_terminate.cpp \
    FFT/rt_nonfinite.cpp \
    FFT/rtGetInf.cpp \
    FFT/rtGetNaN.cpp \
    channelset.cpp \
    stft.cpp \
    fftset.cpp \
    test_timer.cpp \
    usbhandle.cpp \
    portset.cpp \
    wifiset.cpp \
    wordengine.cpp


HEADERS  += mainwindow.h \
    class/glazer_analyse.h \
    connect.h \
    debugwidget.h \
    myframe.h \
    signalprocess.h \
    Iir.h \
    glazer.h \
    qcustomplot/qcustomplot.h \
    iir/Biquad.h \
    iir/Butterworth.h \
    iir/Cascade.h \
    iir/ChebyshevI.h \
    iir/ChebyshevII.h \
    iir/Common.h \
    iir/Custom.h \
    iir/Layout.h \
    iir/MathSupplement.h \
    iir/PoleFilter.h \
    iir/RBJ.h \
    iir/State.h \
    iir/Types.h \
    FFT/FFT.h \
    FFT/fft2.h \
    FFT/FFT_emxAPI.h \
    FFT/FFT_emxutil.h \
    FFT/FFT_initialize.h \
    FFT/FFT_terminate.h \
    FFT/FFT_types.h \
    FFT/rt_nonfinite.h \
    FFT/rtGetInf.h \
    FFT/rtGetNaN.h \
    FFT/rtwtypes.h \
    channelset.h \
    stft.h \
    fftset.h \
    test_timer.h \
    usbhandle.h \
    portset.h \
    wifiset.h \
    wordengine.h




FORMS    += mainwindow.ui \
    debugwidget.ui \
    glazer.ui \
    channelset.ui \
    stft.ui \
    fftset.ui \
    portset.ui \
    test_timer.ui \
    wifiset.ui

DISTFILES +=

RESOURCES += \
    zjueeg.qrc

CONFIG += resources_big

INCLUDEPATH += D:\ShengRuoWenHua\ZJUEEG_bk_remove_et\ZJUEEG\class

