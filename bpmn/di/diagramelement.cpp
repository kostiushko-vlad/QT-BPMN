#include "diagramelement.h"
#include <xmldom/xmlmodeldocument.h>
#include <xmldom/xmltag.h>
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class DiagramElementPrivate
{
public:
    XmlDom::XmlReferenceAttribute *bpmnElement = nullptr;
};
}

DiagramElement::DiagramElement(XmlDom::XmlTag *tag)
: BaseElement(tag), d_ptr(new DiagramElementPrivate)
{
    d_ptr->bpmnElement = attributeBuilder()->createReferenceAttribute("id", "bpmnElement", this, &DiagramElement::bpmnElementChanged);
    if(id().isEmpty())
        setId(document()->nextUniqueId(tag->name()));
}

DiagramElement::~DiagramElement()
{

}
BaseElement *DiagramElement::bpmnElement()
{
    return d_ptr->bpmnElement->referenceElement<BaseElement*>();
}

void DiagramElement::setBpmnElement(BaseElement *value)
{
    d_ptr->bpmnElement->setReferenceElement(value);
    if(value) {
        setObjectName(tag()->name() + " -> "+ value->tag()->name());
    }

}

}
}

