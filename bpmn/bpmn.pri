DEFINES += BPMN_LIBRARY
QT += qml
PRECOMPILED_HEADER = bpmntypes.h
INCLUDEPATH = ../
HEADERS += \
        activity.h \
        bpmn_global.h \
        bpmndi/bpmndiagram.h \
        bpmndi/bpmnedge.h \
        bpmndi/bpmnlabel.h \
        bpmndi/bpmnplane.h \
        bpmndi/bpmnshape.h \
        bpmnfactory.h \
        bpmnutils.h \
        endevent.h \
        event.h \
        extensionelements.h \
        process.h \
        dc/bounds.h \
        dc/point.h \
        di/diagram.h \
        di/diagramelement.h \
        di/edge.h \
        di/label.h \
        di/labelededge.h \
        di/labeledshape.h \
        di/node.h \
        di/plane.h \
        di/shape.h \
        di/waypoint.h \
        artifact.h \
        association.h \
        baseelement.h \
        baseelement_p.h \
        definitions.h \
        documentation.h \
        excusivegateway.h \
        expression.h \
        extension.h \
        extensiondefinition.h \
        flowelement.h \
        flownode.h \
        formalexpression.h \
        gateway.h \
        rootelement.h \
        sequenceflow.h \
        global.h \
        outgoing.h \
        incoming.h \
        bpmn_constants.h \
        startevent.h \
        textannotation.h

SOURCES += \
        activity.cpp \
        bpmndi/bpmndiagram.cpp \
        bpmndi/bpmnedge.cpp \
        bpmndi/bpmnlabel.cpp \
        bpmndi/bpmnplane.cpp \
        bpmndi/bpmnshape.cpp \
        bpmnfactory.cpp \
        bpmnutils.cpp \
        dc/bounds.cpp \
        dc/point.cpp \
        di/diagram.cpp \
        di/diagramelement.cpp \
        di/edge.cpp \
        di/label.cpp \
        di/labelededge.cpp \
        di/labeledshape.cpp \
        di/node.cpp \
        di/plane.cpp \
        di/shape.cpp \
        di/waypoint.cpp \
        artifact.cpp \
        association.cpp \
        baseelement.cpp \
        definitions.cpp \
        documentation.cpp \
        endevent.cpp \
        event.cpp \
        excusivegateway.cpp \
        expression.cpp \
        extension.cpp \
        extensiondefinition.cpp \
        extensionelements.cpp \
        flowelement.cpp \
        flownode.cpp \
        formalexpression.cpp \
        gateway.cpp \
        process.cpp \
        rootelement.cpp \
        sequenceflow.cpp \
        outgoing.cpp \
        incoming.cpp \
        startevent.cpp \
        textannotation.cpp

