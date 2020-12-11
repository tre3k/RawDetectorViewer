QT += core gui widgets printsupport

CONFIG += c++2a
QTPLUGIN += qsvg

TEMPLATE = app
TARGET = rawdetectorviewer

SOURCES = main.cpp \
          data2d.cpp \
          mainwindow.cpp \
          neutrondata.cpp \
          plot.cpp \
          plot1d.cpp \
          plot2d.cpp \
          qcustomplot.cpp

HEADERS += \
        data2d.h \
        mainwindow.h \
        neutrondata.h \
        plot.h \
        plot1d.h \
        plot2d.h \
        qcustomplot.h
#RESOURCES += resources.qrc
