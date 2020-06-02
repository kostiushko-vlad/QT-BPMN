#include "outgoing.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class OutgoingPrivate
{
public:

};
}

Outgoing::Outgoing(XmlDom::XmlTag *tag)
: BaseElement(tag), d_ptr(new OutgoingPrivate)
{

}

Outgoing::~Outgoing()
{

}

}

