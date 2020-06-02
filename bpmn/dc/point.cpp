#include "point.h"
namespace Bpmn {
namespace Dc {
// Private declaration
using namespace Internal;
namespace Internal {
class PointPrivate
{
public:
    XmlDom::XmlAttribute* x = nullptr;
    XmlDom::XmlAttribute* y = nullptr;

};
}

Point::Point(XmlDom::XmlTag *tag)
: BaseElement(tag), d_ptr(new PointPrivate)
{
    d_ptr->x = attributeBuilder()->createAttribute("x", this, &Point::xChanged);
    d_ptr->y = attributeBuilder()->createAttribute("y", this, &Point::yChanged);
}

Point::~Point()
{

}

qreal Point::x()
{
    return d_ptr->x->value<qreal>();
}

void Point::setX(qreal value)
{
    d_ptr->x->setValue(value);
}

qreal Point::y()
{
    return d_ptr->y->value<qreal>();
}

void Point::setY(qreal value)
{
    d_ptr->y->setValue(value);
}

}
}

