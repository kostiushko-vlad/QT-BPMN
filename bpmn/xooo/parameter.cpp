#include "parameter.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class ParameterPrivate
{
public:
    XmlDom::XmlAttribute *name = nullptr;
    XmlDom::XmlAttribute *type = nullptr;
    XmlDom::XmlAttribute *value = nullptr;
    XmlDom::XmlAttribute *collectionType = nullptr;

};
}

Parameter::Parameter(XmlDom::XmlTag *tag)
        : BaseElement(tag), d_ptr(new ParameterPrivate)
{
    d_ptr->name = attributeBuilder()->createAttribute("name", this, &Parameter::nameChanged);
    d_ptr->type = attributeBuilder()->createAttribute("type", this, &Parameter::typeChanged);
    d_ptr->value = attributeBuilder()->createAttribute("value", this, &Parameter::valueChanged);
    d_ptr->collectionType = attributeBuilder()->createAttribute("collection_type", this, &Parameter::collectionTypeChanged);
    d_ptr->collectionType->setEnumerator(Contants::staticMetaObject, "CollectionType");
    d_ptr->collectionType->setValue(Contants::CollectionType::None);
}

Parameter::~Parameter()
{

}
QString Parameter::name() const
{
    return d_ptr->name->toString();
}

void Parameter::setName(const QString &value)
{
    d_ptr->name->setValue(value);
}

QString Parameter::type() const
{
    return d_ptr->type->toString();
}

void Parameter::setType(const QString &value)
{
    d_ptr->type->setValue(value);
}

QString Parameter::value() const
{
    return d_ptr->value->toString();
}

void Parameter::setValue(const QString &value)
{
    d_ptr->value->setValue(value);
}

Contants::CollectionType Parameter::collectionType() const
{
    return d_ptr->collectionType->value<Contants::CollectionType>();
}

void Parameter::setCollectionType(Contants::CollectionType collectionType)
{
    d_ptr->collectionType->setValue(collectionType);
}

}
}
