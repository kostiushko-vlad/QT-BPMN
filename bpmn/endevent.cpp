#include "endevent.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class EndEventPrivate
{
public:

};
}

EndEvent::EndEvent(XmlDom::XmlTag *tag)
        : Event(tag), d_ptr(new EndEventPrivate)
{

}

EndEvent::~EndEvent()
{

}

}

