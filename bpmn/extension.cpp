#include "extension.h"
#include "bpmn/extensiondefinition.h"
#include <QVariant>
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ExtensionPrivate
{
public:
    ExtensionPrivate(Extension *ext): q(ext){}
    QQmlListProperty<ExtensionDefinition> getDefinitions();
    XmlDom::XmlAttribute *name = nullptr;
    XmlDom::XmlChildListAttribute* extensions = nullptr;
    QQmlListProperty<BaseElement> getExtensionElements();

    /*!
     * \brief if extension contains any children, thne remove it
     */
    void removeEmptyExtension();

private:
    Extension *q = nullptr;
};

void ExtensionPrivate::removeEmptyExtension()
{
    XmlDom::XmlModelElement *parentElement = q->parentElement();
    parentElement->removeChild(q);
}

}

Extension::Extension(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new ExtensionPrivate(this))
{
    d_ptr->name = attributeBuilder()->createAttribute("id", this, &Extension::nameChanged);
//    connect(this, &Extension::childModelsChanged, [=]{
//        if(childModels().count() == 0)
//            d_ptr->removeEmptyExtension();
//    });
}

Extension::~Extension()
{

}

QString Extension::name() const
{
    return d_ptr->name->toString();
}

void Extension::setName(const QString &name)
{
    return d_ptr->name->setValue(name);
}

}
#include "moc_extension.cpp"
