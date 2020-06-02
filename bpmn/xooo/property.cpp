#include "property.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class PropertyPrivate
{
public:
    XmlDom::XmlAttribute *name = nullptr;
    XmlDom::XmlAttribute *type = nullptr;
    XmlDom::XmlAttribute *value = nullptr;
};
}

Property::Property(XmlDom::XmlTag *tag)
        : BaseElement(tag), d_ptr(new PropertyPrivate)
{
    d_ptr->name = attributeBuilder()->createAttribute("name", this, &Property::nameChanged);
    d_ptr->type = attributeBuilder()->createAttribute("type", this, &Property::typeChanged);
    d_ptr->value = attributeBuilder()->createAttribute("value", this, &Property::valueChanged);
}

Property::~Property()
{

}

QString Property::name() const
{
    return d_ptr->name->toString();
}

void Property::setName(const QString &value)
{
    d_ptr->name->setValue(value);
}

QString Property::value() const
{
    return d_ptr->value->toString();
}

void Property::setValue(const QString &value)
{
    d_ptr->value->setValue(value);
}
}
}

