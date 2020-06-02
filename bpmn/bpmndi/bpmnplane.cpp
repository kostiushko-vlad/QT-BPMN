#include "bpmnplane.h"
#include "bpmn/bpmn_constants.h"
namespace Bpmn {
namespace BpmnDi {
// Private declaration
using namespace Internal;
namespace Internal {
class BpmnPlanePrivate
{
public:

};
}

BpmnPlane::BpmnPlane(XmlDom::XmlTag *tag)
    : Di::Plane(tag), d_ptr(new BpmnPlanePrivate)
{
}

BpmnPlane::~BpmnPlane()
{

}

}
}

