TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tinyxml/tinyxml2.cpp \
\
    parsable/AbstractXMLParsableObject.cpp \
    parsable/ParsableDestination.cpp \
    parsable/ParsableHeader.cpp \
\
    buildable/AbstractXMLBuildableObject.cpp \
    buildable/BuildableDestination.cpp \
    buildable/BuildableHeader.cpp \
    conversion/byteConversion.cpp

OTHER_FILES +=

HEADERS += \
    tinyxml/tinyxml2.h \
\
    parsable/AbstractXMLParsableObject.h \
    parsable/ParsableDestination.h \
    parsable/ParsableHeader.h \
\
    buildable/AbstractXMLBuildableObject.h \
    buildable/BuildableDestination.h \
    buildable/BuildableHeader.h \
    conversion/byteConversion.h

