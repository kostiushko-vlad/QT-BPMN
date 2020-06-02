#include "bpmndiagram.h"
#include "bpmnplane.h"
#include "bpmn/bpmn_constants.h"
namespace Bpmn {
namespace BpmnDi {
// Private declaration
using namespace Internal;
namespace Internal {
class BpmnDiagramPrivate
{
public:
    XmlDom::XmlChildAttribute *plane = nullptr;

};
}

BpmnDiagram::BpmnDiagram(XmlDom::XmlTag *tag)
    : Di::Diagram(tag), d_ptr(new BpmnDiagramPrivate)
{
    d_ptr->plane = attributeBuilder()->createChildAttribute<Bpmn::BpmnDi::BpmnPlane>(this, &BpmnDiagram::planeChanged);
}

BpmnDiagram::~BpmnDiagram()
{

}

BpmnPlane *BpmnDiagram::plane()
{
    return d_ptr->plane->element<BpmnPlane*>();
}

void BpmnDiagram::setPlane(BpmnPlane *value)
{
    d_ptr->plane->setElement(value);
}
}
}

