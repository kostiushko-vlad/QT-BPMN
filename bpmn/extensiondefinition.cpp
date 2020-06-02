#include "extensiondefinition.h"
#include "bpmn_constants.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ExtensionDefinitionPrivate
{
public:
    XmlDom::XmlAttribute* name = nullptr;
    XmlDom::XmlAttribute* value = nullptr;
};
}

ExtensionDefinition::ExtensionDefinition(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new ExtensionDefinitionPrivate)
{
    d_ptr->name = attributeBuilder()->createAttribute("name", this, &ExtensionDefinition::nameChanged);
    d_ptr->value = attributeBuilder()->createAttribute("value", this, &ExtensionDefinition::valueChanged);
}

ExtensionDefinition::~ExtensionDefinition()
{

}

QString ExtensionDefinition::name() const
{
    return d_ptr->name->toString();
}

void ExtensionDefinition::setName(const QString &value)
{
    d_ptr->name->setValue(value);
}

QVariant ExtensionDefinition::value() const
{
    return d_ptr->value->value();
}

void ExtensionDefinition::setValue(const QVariant &value)
{
    d_ptr->value->setValue(value);
}

}

