#include "label.h"
#include "bpmn/dc/bounds.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class LabelPrivate
{
public:
    XmlDom::XmlChildAttribute* bounds = nullptr;
};
}

Label::Label(XmlDom::XmlTag *tag)
: Node(tag), d_ptr(new LabelPrivate)
{
    d_ptr->bounds = attributeBuilder()->createChildAttribute<Bpmn::Dc::Bounds>(this, &Label::boundsChanged);
}

Label::~Label()
{

}

Dc::Bounds *Label::bounds()
{
    return d_ptr->bounds->element<Dc::Bounds*>();
}

void Label::setBounds(Dc::Bounds *value)
{
    d_ptr->bounds->setElement(value);
}
}
}

