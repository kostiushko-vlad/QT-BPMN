QT += qml xml
DEFINES += XMLDOM_LIBRARY
INCLUDEPATH = ../

HEADERS += \
    xmlattributebuilder.h \
    xmlattributes.h \
    xmldom_global.h \
    xmlmodeldocument.h \
    xmlmodelelementtypebuilder.h \
    xmlmodelsfactory.h \
    xmltag.h \
    xmldocument.h \
    xmlmodelelement.h

SOURCES += \
    xmlattributes.cpp \
    xmlmodeldocument.cpp \
    xmlmodelelementtypebuilder.cpp \
    xmlmodelsfactory.cpp \
    xmltag.cpp \
    xmldocument.cpp \
    xmlattributebuilder.cpp \
    xmlmodelelement.cpp

