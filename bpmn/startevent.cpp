#include "startevent.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class StartEventPrivate
{
public:

};
}

StartEvent::StartEvent(XmlDom::XmlTag *tag)
        : Event(tag), d_ptr(new StartEventPrivate)
{

}

StartEvent::~StartEvent()
{

}

}

