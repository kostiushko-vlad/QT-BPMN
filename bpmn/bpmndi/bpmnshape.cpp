#include "bpmnshape.h"
#include "bpmn/bpmn_constants.h"
namespace Bpmn {
namespace BpmnDi {
// Private declaration
using namespace Internal;
namespace Internal {
class BpmnShapePrivate
{
public:
    XmlDom::XmlAttribute *isHorizontal = nullptr;
    XmlDom::XmlAttribute *isExpanded = nullptr;
    XmlDom::XmlAttribute *isMarkerVisible = nullptr;
};
}

BpmnShape::BpmnShape(XmlDom::XmlTag *tag)
: LabeledShape(tag), d_ptr(new BpmnShapePrivate)
{
    d_ptr->isHorizontal = attributeBuilder()->createAttribute("isHorizontal", this, &BpmnShape::isHorizontalChanged);
    d_ptr->isExpanded = attributeBuilder()->createAttribute("isExpanded", this, &BpmnShape::isExpandedChanged);
    d_ptr->isMarkerVisible = attributeBuilder()->createAttribute("isMarkerVisible", this, &BpmnShape::isMarkerVisibleChanged);
    setObjectName("BPMNShape->" +  bpmnElement()->tag()->name());
}

BpmnShape::~BpmnShape()
{

}

bool BpmnShape::isHorizontal()
{
    return d_ptr->isHorizontal->value<bool>();
}

void BpmnShape::setIsHorizontal(bool value)
{
    d_ptr->isHorizontal->setValue(value);
}

bool BpmnShape::isExpanded()
{
    return d_ptr->isExpanded->value<bool>();
}

void BpmnShape::setIsExpanded(bool value)
{
    d_ptr->isExpanded->setValue(value);
}

bool BpmnShape::isMarkerVisible()
{
    return d_ptr->isMarkerVisible->value<bool>();
}

void BpmnShape::setIsMarkerVisible(bool value)
{
    d_ptr->isMarkerVisible->setValue(value);
}
}
}

