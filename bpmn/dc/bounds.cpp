#include "bounds.h"
#include "bpmn/bpmn_constants.h"
namespace Bpmn {
namespace Dc {
// Private declaration
using namespace Internal;
namespace Internal {
class BoundsPrivate
{
public:
    XmlDom::XmlAttribute* x = nullptr;
    XmlDom::XmlAttribute* y = nullptr;
    XmlDom::XmlAttribute* width = nullptr;
    XmlDom::XmlAttribute* height = nullptr;
};
}

Bounds::Bounds(XmlDom::XmlTag *tag)
: BaseElement(tag), d_ptr(new BoundsPrivate)
{
    // Init attributes
    d_ptr->x = attributeBuilder()->createAttribute("x", this, &Bounds::xChanged);
    d_ptr->y = attributeBuilder()->createAttribute("y", this, &Bounds::yChanged);
    d_ptr->width = attributeBuilder()->createAttribute("width", this, &Bounds::widthChanged);
    d_ptr->height = attributeBuilder()->createAttribute("height", this, &Bounds::heightChanged);
}

Bounds::~Bounds()
{

}

QRectF Bounds::rect() const
{
    return QRectF(x(), y(), width(), height());
}

qreal Bounds::x() const
{
    return d_ptr->x->value<qreal>();
}

void Bounds::setX(qreal value)
{
    d_ptr->x->setValue(value);
}

qreal Bounds::y() const
{
    return d_ptr->y->value<qreal>();
}

void Bounds::setY(qreal value)
{
    d_ptr->y->setValue(value);
}

qreal Bounds::width() const
{
    return d_ptr->width->value<qreal>();
}

void Bounds::setWidth(qreal value)
{
    d_ptr->width->setValue(value);
}

qreal Bounds::height() const
{
    return d_ptr->height->value<qreal>();
}

void Bounds::setHeight(qreal value)
{
    d_ptr->height->setValue(value);
}
}
}

