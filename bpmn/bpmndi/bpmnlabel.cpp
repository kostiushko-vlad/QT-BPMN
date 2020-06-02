#include "bpmnlabel.h"

namespace Bpmn {
namespace BpmnDi {
// Private declaration
using namespace Internal;
namespace Internal {
class BpmnLabelPrivate
{
public:

};
}

BpmnLabel::BpmnLabel(XmlDom::XmlTag *tag)
: Label(tag), d_ptr(new BpmnLabelPrivate)
{

}

BpmnLabel::~BpmnLabel()
{

}
}
}

