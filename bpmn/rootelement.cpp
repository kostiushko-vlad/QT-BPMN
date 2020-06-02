#include "rootelement.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class RootElementPrivate
{
public:

};
}

RootElement::RootElement(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new RootElementPrivate)
{

}

RootElement::~RootElement()
{

}
}

