#include "properties.h"
#include "property.h"
#include "flowelement.h"
#include "bpmn/bpmnfactory.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class PropertiesPrivate
{
public:
    PropertiesPrivate(Properties *p):q(p){}
    XmlDom::XmlChildListAttribute *properties = nullptr;
    QQmlListProperty<Property> getProperties();
private:
    Properties *q = nullptr;
};

QQmlListProperty<Property> PropertiesPrivate::getProperties()
{
    QList<Property*> elements = Utils::toList<Property*>(properties->elements());
    return QQmlListProperty<Property>(q, elements);
}

}

Properties::Properties(XmlDom::XmlTag *tag)
    : Extension(tag), d_ptr(new PropertiesPrivate(this))
{
    d_ptr->properties = attributeBuilder()->createChildListAttribute<Property>(this, &Properties::propertiesChanged);
}

Properties::~Properties()
{

}

QList<Property *> Properties::properties() const
{
    return d_ptr->properties->elements<Property*>();
}

Property *Properties::findProperty(const QString &name)
{
    for(Property *p : properties()){
        if(p->name() == name)
            return p;
    }
    return nullptr;
}

void Properties::removeProperty(const QString &name)
{
    Property *property = findProperty(name);
    removeChild(property);
    property->deleteLater();
}

Property * Properties::insertProperty(const QString &name, const QString &value)
{
    XOOO_GUARD(name.isEmpty(), return nullptr)

    Property *property = findProperty(name);

    if(!property){
        property = BpmnFactory::instance()->createInstanceOfModel<Property>(document(), this);
    }

    property->setName(name);
    property->setValue(value);
    if(value.isEmpty()){
        removeChild(property);
    }
    // Notify property child changed for CallActivity or image
    if(auto containerElement = qobject_cast<BaseElement*>(parentElement()->parentElement())){
        emit containerElement->propertyChanged(name);
    }
    emit propertyChanged(name);
    return property;
}
}
}

#include "moc_properties.cpp"
