#include "event.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class EventPrivate
{
public:

};
}

Event::Event(XmlDom::XmlTag *tag)
        : FlowNode(tag), d_ptr(new EventPrivate)
{

}

Event::~Event()
{

}

}

