INCLUDEPATH += $PWD
DEPENDPATH += $PWD

HEADERS += \
    Filters/filter.h \
    Filters/adaptivethresholdfilter.h \
    Filters/colorspaceconversionfilter.h \
    Filters/filterobserver.h \
    Filters/thresholdfilter.h \
    Filters/dilatefilter.h \
    Filters/erodefilter.h

SOURCES += \
    Filters/filter.cpp \
    Filters/adaptivethresholdfilter.cpp \
    Filters/colorspaceconversionfilter.cpp \
    Filters/filterobserver.cpp \
    Filters/thresholdfilter.cpp \
    Filters/dilatefilter.cpp \
    Filters/erodefilter.cpp
