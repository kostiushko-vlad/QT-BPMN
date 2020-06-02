#include "contextvariable.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class ContextVariablePrivate
{
public:
    XmlDom::XmlAttribute *name = nullptr;
    XmlDom::XmlAttribute *type = nullptr;
    XmlDom::XmlAttribute *value = nullptr;
    XmlDom::XmlAttribute *collectionType = nullptr;

};
}

ContextVariable::ContextVariable(XmlDom::XmlTag *tag)
        : BaseElement(tag), d_ptr(new ContextVariablePrivate)
{
    d_ptr->name = attributeBuilder()->createAttribute("name", this, &ContextVariable::nameChanged);
    d_ptr->type = attributeBuilder()->createAttribute("type", this, &ContextVariable::typeChanged);
    d_ptr->value = attributeBuilder()->createAttribute("value", this, &ContextVariable::valueChanged);
    d_ptr->collectionType = attributeBuilder()->createAttribute("collection_type", this, &ContextVariable::collectionTypeChanged);
    d_ptr->collectionType->setEnumerator(Contants::staticMetaObject, "CollectionType");
    d_ptr->collectionType->setValue(Contants::CollectionType::None);
}

ContextVariable::~ContextVariable()
{

}

QString ContextVariable::name() const
{
    return d_ptr->name->toString();
}

void ContextVariable::setName(const QString &value)
{
    d_ptr->name->setValue(value);
}

QString ContextVariable::type() const
{
    return d_ptr->type->toString();
}

void ContextVariable::setType(const QString &value)
{
    d_ptr->type->setValue(value);
}

QString ContextVariable::value() const
{
    return d_ptr->value->toString();
}

void ContextVariable::setValue(const QString &value)
{
    d_ptr->value->setValue(value);
}

Contants::CollectionType ContextVariable::collectionType() const
{
    return d_ptr->collectionType->value<Contants::CollectionType>();
}

void ContextVariable::setCollectionType(Contants::CollectionType collectionType)
{
    d_ptr->collectionType->setValue(collectionType);
}
}
}

