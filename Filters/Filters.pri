INCLUDEPATH += $PWD
DEPENDPATH += $PWD

HEADERS += \
    Filters/filter.h \
    Filters/adaptivethresholdfilter.h \
    Filters/colorspaceconversionfilter.h \
    Filters/filterobserver.h

SOURCES += \
    Filters/filter.cpp \
    Filters/adaptivethresholdfilter.cpp \
    Filters/colorspaceconversionfilter.cpp \
    Filters/filterobserver.cpp
