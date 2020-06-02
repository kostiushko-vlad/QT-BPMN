#include "xmlattributebuilder.h"
#include "xmltag.h"
#include "xmlattributes.h"
#include "xmlmodelelement.h"
#include "xmlmodeldocument.h"
#include "xmldocument.h"
#include "xmlmodelsfactory.h"
#include "xmlmodelelementtypebuilder.h"
namespace XmlDom {
// Private declaration
using namespace Internal;
namespace Internal {
class XmlAttributeBuilderPrivate
{
public:
    XmlModelElement *modelElement = nullptr;
    XmlModelsFactory *modelsFactory = nullptr;
    XmlAttributeBuilder::AttributeListener listenter;
    void finalize(XmlBaseAttribute *attribute);
};

void XmlAttributeBuilderPrivate::finalize(XmlBaseAttribute *attribute)
{
    listenter(attribute);
}

}

XmlAttributeBuilder::XmlAttributeBuilder(XmlModelElement *modelElement)
: d_ptr(new XmlAttributeBuilderPrivate)
{
    d_ptr->modelElement = modelElement;
}

XmlAttributeBuilder::~XmlAttributeBuilder()
{

}

void XmlAttributeBuilder::setListener(const XmlAttributeBuilder::AttributeListener &listener)
{
    d_ptr->listenter = listener;
}

XmlModelElement *XmlAttributeBuilder::modelElement() const
{
    return d_ptr->modelElement;
}

XmlAttribute *XmlAttributeBuilder::createAttribute(const QString &namespaceUri, const QString &name)
{
    auto attr = new XmlAttribute(d_ptr->modelElement, namespaceUri, name);
    d_ptr->finalize(attr);
    return attr;
}

XmlReferenceAttribute *XmlAttributeBuilder::createReferenceAttribute(const QString &identifierName, const QString &namespaceUri, const QString &name)
{
    auto attr = new XmlReferenceAttribute(d_ptr->modelElement, identifierName, namespaceUri, name);
    d_ptr->finalize(attr);
    return attr;
}

// Looks for model factory in model element, and returns found type
XmlModelElementType *getType(XmlModelElement *element, int typeId) {
    return element->modelsFactory()->typeBuilder()->type(typeId);
}

XmlReferenceListAttribute *XmlAttributeBuilder::createReferenceListAttribute(int typeId, const QString &identifierName)
{
    XmlModelElementType *modelType = getType(modelElement(), typeId);
    auto attr = new XmlReferenceListAttribute(d_ptr->modelElement, identifierName,  modelType);
    d_ptr->finalize(attr);
    return attr;
}

XmlChildAttribute *XmlAttributeBuilder::createChildAttribute(int typeId)
{
    XmlModelElementType *modelType = getType(modelElement(), typeId);
    auto attr = new XmlChildAttribute(d_ptr->modelElement, modelType);
    d_ptr->finalize(attr);
    return attr;
}

XmlChildListAttribute *XmlAttributeBuilder::createChildListAttribute(int typeId)
{
    XmlModelElementType *modelType = getType(modelElement(), typeId);
    auto attr = new XmlChildListAttribute(d_ptr->modelElement, modelType);
    d_ptr->finalize(attr);
    return attr;
}

}

