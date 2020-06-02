#include "bpmnedge.h"
#include "bpmnlabel.h"
#include "bpmn/bpmn_constants.h"
namespace Bpmn {
namespace BpmnDi {
// Private declaration
using namespace Internal;
namespace Internal {
class BpmnEdgePrivate
{
public:
    XmlDom::XmlReferenceAttribute *label = nullptr;

    XmlDom::XmlReferenceAttribute *sourceElement = nullptr;
    XmlDom::XmlReferenceAttribute *targetElement = nullptr;
};
}

BpmnEdge::BpmnEdge(XmlDom::XmlTag *tag)
: LabeledEdge(tag), d_ptr(new BpmnEdgePrivate)
{
    d_ptr->label = attributeBuilder()->createReferenceAttribute("id", "label", this, &BpmnEdge::labelChanged);
    d_ptr->sourceElement = attributeBuilder()->createReferenceAttribute("id", "sourceElement", this, &BpmnEdge::sourceElementChanged);
    d_ptr->targetElement = attributeBuilder()->createReferenceAttribute("id", "targetElement", this, &BpmnEdge::targetElementChanged);
}

BpmnEdge::~BpmnEdge()
{

}

BpmnLabel *BpmnEdge::label()
{
    return d_ptr->label->referenceElement<BpmnLabel*>();
}

void BpmnEdge::setLabel(BpmnLabel *value)
{
    d_ptr->label->setReferenceElement(value);
}

BaseElement *BpmnEdge::sourceElement()
{
    return d_ptr->sourceElement->referenceElement<BaseElement*>();
}

void BpmnEdge::setSourceElement(BaseElement *value)
{
    d_ptr->sourceElement->setReferenceElement(value);
}

BaseElement *BpmnEdge::targetElement()
{
    return d_ptr->targetElement->referenceElement<BaseElement*>();
}

void BpmnEdge::setTargetElement(BaseElement *value)
{
    d_ptr->targetElement->setReferenceElement(value);
}
}
}

