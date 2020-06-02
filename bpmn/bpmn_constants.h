#pragma once
#include <bpmn/bpmn_global.h>
#include <QMap>
#include <QObject>

namespace Bpmn {
namespace Contants {
Q_NAMESPACE_EXPORT(BPMN_LIBRARY_EXPORT)

/** The XSI namespace */
const char XSI_NS[]            = "http://www.w3.org/2001/XMLSchema-instance";

/** The BPMN 2.0 namespace */
const char BPMN20_NS[]         = "http://www.omg.org/spec/BPMN/20100524/MODEL";

/** The BPMNDI namespace */
const char BPMNDI_NS[]         = "http://www.omg.org/spec/BPMN/20100524/DI";

/** The DI namespace */
const char DI_NS[]             = "http://www.omg.org/spec/DD/20100524/DI";

/** The DC namespace */
const char DC_NS[]             = "http://www.omg.org/spec/DD/20100524/DC";

enum CollectionType {
    None,
    List,
    Map
};
Q_ENUM_NS(CollectionType)
inline QString typeName(Contants::CollectionType collectionType, const QString &typeName) {
    QString type = typeName;
    if(collectionType == Contants::List) {
        type = "List[" + type + "]";
    }
    if(collectionType == Contants::Map) {
        type = "Map[" + type + "]";
    }
    return type;
}
inline QString getType(const QString &typeName) {
    QString type = typeName;
    if(type.contains("List[") || type.contains("Map[")){
        int start = type.indexOf('[') + 1;
        int end = type.indexOf(']');

        if(start != -1 && end != -1){
            type = type.mid(start, end - start);
        }
    }
    return type;
}
inline CollectionType getCollectionType(const QString &typeName) {
    CollectionType type = Contants::CollectionType::None;
    if(typeName.contains("List[")){
        type = Contants::CollectionType::List;
    }
    if(typeName.contains("Map[")){
        type = Contants::CollectionType::List;
    }
    return type;
}

const char BOOL[] = "Bool";
const char UINT8[] = "UInt8";
const char INT8[] = "Int8";
const char UINT16[] = "UInt16";
const char INT16[] = "Int16";
const char UINT32[] = "UInt32";
const char INT32[] = "Int32";
const char UINT64[] = "UInt64";
const char INT64[] = "Int64";
const char FLOAT[] = "Float";
const char DOUBLE[] = "Double";
const char STRING[] = "String";
const char DATETIME[] = "DateTime";
const char LIST_BOOL[] = "List[Bool]";
const char LIST_UINT8[] = "List[UInt8]";
const char LIST_INT8[] = "List[Int8]";
const char LIST_UINT16[] = "List[UInt16]";
const char LIST_INT16[] = "List[Int16]";
const char LIST_UINT32[] = "List[UInt32]";
const char LIST_INT32[] = "List[Int32]";
const char LIST_UINT64[] = "List[UInt64]";
const char LIST_INT64[] = "List[Int64]";
const char LIST_DOUBLE[] = "List[Double]";
const char LIST_STRING[] = "List[String]";
const char LIST_DATETIME[] = "List[DateTime]";

static QStringList KNOWN_VARIABLETYPES{
    BOOL,
    UINT8,
    INT8,
    UINT16,
    INT16,
    UINT32,
    INT32,
    UINT64,
    INT64,
    FLOAT,
    DOUBLE,
    STRING,
    DATETIME,
    LIST_BOOL,
    LIST_UINT8,
    LIST_INT8,
    LIST_UINT16,
    LIST_INT16,
    LIST_UINT32,
    LIST_INT32,
    LIST_UINT64,
    LIST_INT64,
    LIST_DOUBLE,
    LIST_STRING,
    LIST_DATETIME
};

// Elements //////////////////////

const char BPMN_ELEMENT_BASE_ELEMENT[] = "baseElement";
const char BPMN_ELEMENT_DEFINITIONS[] = "definitions";
const char BPMN_ELEMENT_DOCUMENTATION[] = "documentation";
const char BPMN_ELEMENT_EXTENSION_ELEMENTS[] = "extensionElements";
const char BPMN_ELEMENT_EXTENSION[] = "extension";
const char BPMN_ELEMENT_EXTENSION_DEFINITION[] = "extensionDefinition";
const char BPMN_ELEMENT_IMPORT[] = "import";
const char BPMN_ELEMENT_RELATIONSHIP[] = "relationship";
const char BPMN_ELEMENT_SOURCE[] = "source";
const char BPMN_ELEMENT_TARGET[] = "target";
const char BPMN_ELEMENT_ROOT_ELEMENT[] = "rootElement";
const char BPMN_ELEMENT_FLOW_ELEMENT[] = "flowElement";
const char BPMN_ELEMENT_FLOW_NODE[] = "flowNode";
const char BPMN_ELEMENT_EXPRESSION[] = "expression";
const char BPMN_ELEMENT_CONDITION_EXPRESSION[] = "conditionExpression";
const char BPMN_ELEMENT_SEQUENCE_FLOW[] = "sequenceFlow";
const char BPMN_ELEMENT_PROCESS[] = "process";
const char BPMN_ELEMENT_INCOMING[] = "incoming";
const char BPMN_ELEMENT_OUTGOING[] = "outgoing";
const char BPMN_ELEMENT_FORMAL_EXPRESSION[] = "formalExpression";
const char BPMN_ELEMENT_SOURCE_REF[] = "sourceRef";
const char BPMN_ELEMENT_TARGET_REF[] = "targetRef";
const char BPMN_ELEMENT_BASE_EVENT[] = "event";
const char BPMN_ELEMENT_START_EVENT[] = "startEvent";
const char BPMN_ELEMENT_END_EVENT[] = "endEvent";
const char BPMN_ELEMENT_GATEWAY[] = "gateway";
const char BPMN_ELEMENT_ACTIVITY[] = "activity";
const char BPMN_ELEMENT_EXCLUSIVE_GATEWAY[] = "exclusiveGateway";
const char BPMN_ELEMENT_ARTIFACT[] = "artifact";
const char BPMN_ELEMENT_ASSOCIATION[] = "association";
const char BPMN_ELEMENT_TEXT_ANNOTATION[] = "textAnnotation";
const char BPMN_ELEMENT_DATA_OBJECT[] = "dataObject";

// DC ////
const char DC_ELEMENT_POINT[] = "Point";
const char DC_ELEMENT_BOUNDS[] = "Bounds";

// DI ////////
const char DI_ELEMENT_DIAGRAM_ELEMENT[] = "DiagramElement";
const char DI_ELEMENT_DIAGRAM[] = "Diagram";
const char DI_ELEMENT_EDGE[] = "Edge";
const char DI_ELEMENT_EXTENSION[] = "extension";
const char DI_ELEMENT_LABELED_EDGE[] = "LabeledEdge";
const char DI_ELEMENT_LABEL[] = "Label";
const char DI_ELEMENT_LABELED_SHAPE[] = "LabeledShape";
const char DI_ELEMENT_NODE[] = "Node";
const char DI_ELEMENT_PLANE[] = "Plane";
const char DI_ELEMENT_SHAPE[] = "Shape";
const char DI_ELEMENT_STYLE[] = "Style";
const char DI_ELEMENT_WAYPOINT[] = "waypoint";

// BPMNDI ///////
const char BPMNDI_ELEMENT_BPMN_DIAGRAM[] = "BPMNDiagram";
const char BPMNDI_ELEMENT_BPMN_PLANE[] = "BPMNPlane";
const char BPMNDI_ELEMENT_BPMN_LABEL_STYLE[] = "BPMNLabelStyle";
const char BPMNDI_ELEMENT_BPMN_SHAPE[] = "BPMNShape";
const char BPMNDI_ELEMENT_BPMN_LABEL[] = "BPMNLabel";
const char BPMNDI_ELEMENT_BPMN_EDGE[] = "BPMNEdge";

}
}
