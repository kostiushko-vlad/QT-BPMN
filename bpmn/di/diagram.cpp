#include "diagram.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class DiagramPrivate
{
public:
    XmlDom::XmlAttribute* name;
    XmlDom::XmlAttribute* resolution;


};
}

Diagram::Diagram(XmlDom::XmlTag *tag)
: RootElement(tag), d_ptr(new DiagramPrivate)
{
    d_ptr->name = attributeBuilder()->createAttribute("name", this, &Diagram::nameChanged);
    d_ptr->resolution = attributeBuilder()->createAttribute("resolution", this, &Diagram::resolutionChanged);
}

Diagram::~Diagram()
{

}

QString Diagram::name()
{
    return d_ptr->name->toString();
}

void Diagram::setName(QString value)
{
    d_ptr->name->setValue(value);
}

qreal Diagram::resolution()
{
    return d_ptr->resolution->value<qreal>();
}

void Diagram::setResolution(qreal value)
{
    d_ptr->resolution->setValue(value);
}

}
}
