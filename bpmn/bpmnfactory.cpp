#include "bpmnfactory.h"
#include <bpmn/bpmntypes.h>
#include <xmldom/xmltag.h>
#include <xmldom/xmldocument.h>
#include <QQmlEngine>
using namespace Bpmn;
namespace Bpmn {
// Private declaration

namespace Internal {
class BpmnFactoryPrivate
{
public:
};

}
using namespace Internal;

static BpmnFactory *m_instance = nullptr;
static BpmnFactoryPrivate *dptr = nullptr;

BpmnFactory::BpmnFactory()
{
    m_instance = this;
    dptr = new BpmnFactoryPrivate;
    init();
}

BpmnFactory::~BpmnFactory()
{
    delete dptr;
}

BpmnFactory *BpmnFactory::instance()
{
    return m_instance;
}

void BpmnFactory::registerNamespaces()
{
    registerNamespace(Bpmn::Contants::BPMN20_NS, "bpmn");
    registerNamespace(Bpmn::Contants::BPMNDI_NS, "bpmndi");
    registerNamespace(Bpmn::Contants::DI_NS, "di");
    registerNamespace(Bpmn::Contants::DC_NS, "dc");
}

void BpmnFactory::registerTypes(XmlDom::XmlModelElementTypeBuilder *typeBuilder)
{
    Artifact::registerType(typeBuilder);
    Association::registerType(typeBuilder);
    BaseElement::registerType(typeBuilder);
    Definitions::registerType(typeBuilder);
    Documentation::registerType(typeBuilder);
    ExcusiveGateway::registerType(typeBuilder);
    Expression::registerType(typeBuilder);
    Extension::registerType(typeBuilder);
    ExtensionDefinition::registerType(typeBuilder);
    ExtensionDefinition::registerType(typeBuilder);
    FlowElement::registerType(typeBuilder);
    FlowNode::registerType(typeBuilder);
    FormalExpression::registerType(typeBuilder);
    Gateway::registerType(typeBuilder);
    Process::registerType(typeBuilder);
    RootElement::registerType(typeBuilder);
    SequenceFlow::registerType(typeBuilder);
    Outgoing::registerType(typeBuilder);
    Incoming::registerType(typeBuilder);
    Activity::registerType(typeBuilder);
    Event::registerType(typeBuilder);
    StartEvent::registerType(typeBuilder);
    EndEvent::registerType(typeBuilder);
    ExtensionElements::registerType(typeBuilder);
    TextAnnotation::registerType(typeBuilder);
    Dc::Bounds::registerType(typeBuilder);
    Dc::Point::registerType(typeBuilder);
    Di::Diagram::registerType(typeBuilder);
    Di::DiagramElement::registerType(typeBuilder);
    Di::Edge::registerType(typeBuilder);
    Di::Label::registerType(typeBuilder);
    Di::LabeledEdge::registerType(typeBuilder);
    Di::LabeledShape::registerType(typeBuilder);
    Di::Node::registerType(typeBuilder);
    Di::Plane::registerType(typeBuilder);
    Di::Shape::registerType(typeBuilder);
    Di::Waypoint::registerType(typeBuilder);
    BpmnDi::BpmnDiagram::registerType(typeBuilder);
    BpmnDi::BpmnEdge::registerType(typeBuilder);
    BpmnDi::BpmnLabel::registerType(typeBuilder);
    BpmnDi::BpmnPlane::registerType(typeBuilder);
    BpmnDi::BpmnShape::registerType(typeBuilder);
    qmlRegisterUncreatableMetaObject(Contants::staticMetaObject, "Bpmn",
                                     1, 0, "Bpmn", "Error: only enums");
}

}

