INCLUDEPATH += $PWD
DEPENDPATH += $PWD

HEADERS += \
    Filters/filter.h \
    Filters/adaptivethresholdfilter.h \
    Filters/colorspaceconversionfilter.h \
    Filters/filterobserver.h \
    Filters/thresholdfilter.h \
    Filters/dilatefilter.h \
    Filters/erodefilter.h \
    Filters/blurfilter.h \
    Filters/histogramequalizationfilter.h \
    Filters/absolutedifferencefilter.h \
    Filters/bitwiseandfilter.h \
    Filters/binaryoperationfilter.h

SOURCES += \
    Filters/filter.cpp \
    Filters/adaptivethresholdfilter.cpp \
    Filters/colorspaceconversionfilter.cpp \
    Filters/filterobserver.cpp \
    Filters/thresholdfilter.cpp \
    Filters/dilatefilter.cpp \
    Filters/erodefilter.cpp \
    Filters/blurfitler.cpp \
    Filters/histogramequalizationfilter.cpp \
    Filters/absolutedifferencefilter.cpp \
    Filters/bitwiseandfilter.cpp \
    Filters/binaryoperationfilter.cpp
