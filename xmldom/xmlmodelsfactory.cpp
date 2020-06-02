#include "xmlmodelsfactory.h"
#include "xmlmodelelement.h"
#include "xmlmodeldocument.h"
#include <xmldom/xmlmodelelementtypebuilder.h>
namespace XmlDom {
// Private declaration
using namespace Internal;
namespace Internal {
class XmlModelsFactoryPrivate
{
public:
    XmlDom::XmlModelElementTypeBuilder typeBuilder;
    QHash<QString, QString> registeredNamespaces;
};
}

XmlModelsFactory::XmlModelsFactory(QObject *parent)
	: QObject(parent), d_ptr(new XmlModelsFactoryPrivate)
{

}

XmlModelsFactory::~XmlModelsFactory()
{

}

XmlModelElementTypeBuilder *XmlModelsFactory::typeBuilder()
{
    return &d_ptr->typeBuilder;
}

XmlTag *XmlModelsFactory::createTag(int typeId, XmlModelDocument *doc)
{
    XmlModelElementType *elementType = d_ptr->typeBuilder.type(typeId);
    return createTag(elementType, doc);
}

XmlTag *XmlModelsFactory::createTag(XmlModelElementType *type, XmlModelDocument *doc)
{
    GUARD(!type, return nullptr)

    auto tag = new XmlTag(type->namespaceUri(), type->typeName(), doc);
    return tag;
}

XmlTag *XmlModelsFactory::createTag(const QString namespaceUri, const QString &name, XmlModelDocument *doc)
{
    XmlModelElementType *elementType = typeBuilder()->type(namespaceUri, name);
    GUARD(!elementType, return nullptr)

    return createTag(elementType, doc);
}

XmlModelElement *XmlModelsFactory::createModel(XmlModelDocument *doc, const QString namespaceUri, const QString &typeName, XmlDom::XmlModelElement *parent)
{
    XmlModelElementType *elementType = typeBuilder()->type(namespaceUri, typeName);
    GUARD(!elementType, return nullptr)

    XmlTag *tag = createTag(elementType, doc);
    return createModel(tag, parent);
}

XmlDom::XmlModelElement *XmlModelsFactory::createModel(XmlDom::XmlTag *tag, XmlDom::XmlModelElement *parentElement)
{
    XmlModelElementType *elementType = typeBuilder()->type(tag);
    if(!elementType){
        qDebug() << "Type cannot be found for tag" << tag->name() << "in document" << tag->document()->fileName();
        return nullptr;
    }
    XmlModelElement *newElement = elementType->newModelElementInstance(tag);

    if(parentElement){
        parentElement->appendChild(newElement);
    }

    emit modelCreated(newElement);
    return newElement;
}

XmlDom::XmlModelElement *XmlModelsFactory::copyModel(XmlDom::XmlModelElement *model, XmlDom::XmlModelDocument *doc)
{
    auto copyTag = new XmlDom::XmlTag(model->tag(), doc);
    //copyTag->setDocument(doc);
    XmlDom::XmlModelElement* modelElement = createModel(copyTag);
    return modelElement;
}

void XmlModelsFactory::registerNamespace(const QString &namespaceUri, const QString &prefix)
{
    d_ptr->registeredNamespaces.insert(namespaceUri, prefix);
}

QHash<QString, QString> XmlModelsFactory::registeredNamespaces() const
{
    return d_ptr->registeredNamespaces;
}
void XmlModelsFactory::init()
{
    registerNamespaces();
    registerTypes(typeBuilder());
    typeBuilder()->buildTypes();
}

void XmlModelsFactory::registerNamespaces()
{

}


}

