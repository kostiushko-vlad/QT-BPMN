#include "extensionelements.h"
#include "extensionelements.h"
#include "extension.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ExtensionElementsPrivate
{
public:
    ExtensionElementsPrivate(ExtensionElements *extension):q(extension){}
    XmlDom::XmlChildListAttribute* elements = nullptr;
    QQmlListProperty<Extension> getElements();
private:
    ExtensionElements *q = nullptr;
};
}

ExtensionElements::ExtensionElements(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new ExtensionElementsPrivate(this))
{
    d_ptr->elements = attributeBuilder()->createChildListAttribute<Extension>(this, &ExtensionElements::extensionElementsChanged);
}

ExtensionElements::~ExtensionElements()
{

}

QList<Extension *> ExtensionElements::elements() const
{
    return d_ptr->elements->elements<Extension*>();
}

QList<Extension *> ExtensionElements::elements(int typeId) const
{
    return toList<Extension*>(d_ptr->elements->elements(typeId));
}

void ExtensionElements::addExtension(XmlModelElement *element) const
{
    d_ptr->elements->append(element);
}

QQmlListProperty<Extension> ExtensionElementsPrivate::getElements()
{
    QList<Extension*> elements = toList<Extension*>(this->elements->elements());
    return QQmlListProperty<Extension>(q, elements);
}
}
#include "moc_extensionelements.cpp"
