#include "association.h"
#include "bpmn_constants.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class AssociationPrivate
{
public:
    XmlDom::XmlAttribute* associationDirection = nullptr;
    XmlDom::XmlReferenceAttribute* sourceRef = nullptr;
    XmlDom::XmlReferenceAttribute* targetRef = nullptr;

};
}

Association::Association(XmlDom::XmlTag *tag)
    : Artifact(tag), d_ptr(new AssociationPrivate)
{
    d_ptr->associationDirection = attributeBuilder()->createAttribute("associationDirection", this, &Association::associationDirectionChanged);
    d_ptr->sourceRef = attributeBuilder()->createReferenceAttribute("id", "sourceRef", this, &Association::sourceRefChanged);
    d_ptr->targetRef = attributeBuilder()->createReferenceAttribute("id", "targetRef", this, &Association::targetRefChanged);
}

Association::~Association()
{

}

Association::AssociationDirection Association::associationDirection() const
{
    return d_ptr->associationDirection->value<AssociationDirection>();
}

void Association::setAssociationDirection(Association::AssociationDirection value)
{
    d_ptr->associationDirection->setValue(value);
}

BaseElement *Association::sourceRef()
{
    return d_ptr->sourceRef->referenceElement<BaseElement*>();
}

void Association::setSourceRef(BaseElement *value)
{
    d_ptr->sourceRef->setReferenceElement(value);
}

BaseElement *Association::targetRef()
{
    return d_ptr->targetRef->referenceElement<BaseElement*>();
}

void Association::setTargetRef(BaseElement *value)
{
    d_ptr->targetRef->setReferenceElement(value);
}
}
