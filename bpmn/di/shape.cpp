#include "shape.h"
#include "bpmn/dc/bounds.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class ShapePrivate
{
public:
    XmlDom::XmlChildAttribute *bounds = nullptr;

};
}

Shape::Shape(XmlDom::XmlTag *tag)
: Node(tag), d_ptr(new ShapePrivate)
{
    d_ptr->bounds = attributeBuilder()->createChildAttribute<Bpmn::Dc::Bounds>(this, &Shape::boundsChanged);
}

Shape::~Shape()
{

}

Dc::Bounds* Shape::bounds()
{
    return d_ptr->bounds->element<Dc::Bounds*>();
}

void Shape::setBounds(Dc::Bounds* value)
{
    d_ptr->bounds->setElement(value);
}
}
}

