#include "incoming.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class IncomingPrivate
{
public:

};
}

Incoming::Incoming(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new IncomingPrivate)
{

}

Incoming::~Incoming()
{

}

}

