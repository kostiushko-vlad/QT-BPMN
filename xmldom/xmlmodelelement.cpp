#include "xmlmodelelement.h"
#include "xmlattributebuilder.h"
#include "xmlmodeldocument.h"
#include "xmlmodelelementtypebuilder.h"
#include "xmlmodelsfactory.h"
#include "xmltag.h"
namespace XmlDom {
// Private declaration
using namespace Internal;
namespace Internal {
class XmlModelElementPrivate
{
public:
    XmlModelElementPrivate(XmlModelElement *element)
        : q(element){}

    XmlTag *tag = nullptr;
    XmlModelElementTypeBuilder *typeBuilder = nullptr;
    QList<XmlBaseAttribute*> attiributes;
    XmlAttributeBuilder *attributeBuilder = nullptr;
    void connectTag();

private:
    XmlModelElement *q = nullptr;
};

}

XmlModelElement::XmlModelElement(XmlDom::XmlTag* tag)
    : QObject(tag), d_ptr(new XmlModelElementPrivate(this))
{
    d_ptr->tag = tag;
    // Connects tag signals with model element
    connect(tag, &XmlTag::childTagsChanged, this, &XmlModelElement::childrenChanged);
    connect(tag, &XmlTag::parentTagChanged, this, &XmlModelElement::parentElementChanged);
    connect(tag, &XmlTag::attributeChanged, this, &XmlModelElement::attributesChanged);

    d_ptr->attributeBuilder = new XmlAttributeBuilder(this);

    // Attribute builder notifies that new attribute is created
    // And should be added to the model
    d_ptr->attributeBuilder->setListener([=](XmlBaseAttribute *attr){
        setAttribute(attr);
    });

    // Set object name for better debugging
    d_ptr->tag->setObjectName(tag->name());
    setObjectName(tag->name());
}

XmlModelElement::~XmlModelElement()
{
    disconnect();
    delete d_ptr->attributeBuilder;
    d_ptr->attributeBuilder = nullptr;
}

XmlTag *XmlModelElement::tag() const
{
    return d_ptr->tag;
}

XmlModelElement *XmlModelElement::parentElement() const
{
    return document()->findModelElement(tag()->parentTag());
}

XmlModelDocument *XmlModelElement::document() const
{
    return tag() ? qobject_cast<XmlModelDocument*>(tag()->document())
                 : nullptr;
}

XmlModelElementType *XmlModelElement::type() const
{
    XmlModelElementType *modelType = document()->modelsFactory()->typeBuilder()->type(tag());
    return modelType;
}

QList<XmlBaseAttribute *> XmlModelElement::attributes() const
{
    return d_ptr->attiributes;
}

XmlBaseAttribute *XmlModelElement::findAttribute(const QString &namespaceUri, const QString &name) const
{
    return findOr(d_ptr->attiributes, nullptr, [=](XmlBaseAttribute *attr){
        return attr->namespaceUri() == namespaceUri && attr->name() == name;
    });
}

void XmlModelElement::setAttribute(XmlBaseAttribute *attribute)
{
    d_ptr->attiributes.append(attribute);
    emit attributesChanged();
}

void XmlModelElement::finilizeCreation()
{

}

void XmlModelElement::clearAttributes()
{
    qDeleteAll(d_ptr->attiributes);
}

QList<XmlModelElement *> XmlModelElement::childElements() const
{
    return toList<XmlModelElement *>(tag()->childTags(),[=](XmlTag *tag){
        XmlModelElement * modelElement = document()->findModelElement(tag);
        if(!modelElement) {
            qDebug() << "Model element is null for tag" << tag->name();
        }
        return modelElement;
    });
}

int XmlModelElement::index() const
{
    return tag()->index();
}

int XmlModelElement::childCount() const
{
    return tag()->childTags().count();
}

void XmlModelElement::appendChild(XmlModelElement *child)
{
    GUARD(!child, return)

    tag()->appendChild(child->tag());
}

void XmlModelElement::insertChild(int index, XmlModelElement *child)
{
    GUARD(!child, return)
    // Some tags can have no parent
    if(child->tag()->parentTag()) {
        child->tag()->parentTag()->removeChild(child->tag());
    }
    tag()->insertChild(index, child->tag());}

void XmlModelElement::removeChild(XmlModelElement *child)
{
    GUARD(!child, return)

    tag()->removeChild(child->tag());
}

void XmlModelElement::moveChild(int oldPos, int newPos)
{
    tag()->moveChild(oldPos, newPos);
}

XmlModelElement *XmlModelElement::childAt(int index) const
{
    return document()->findModelElement(tag()->child(index));
}

int XmlModelElement::childIndex(const XmlModelElement *child) const
{
    GUARD(!child, return -1)

    return tag()->childIndex(child->tag());
}

void XmlModelElement::clearChildren()
{
    tag()->clearChildren();
}

QList<XmlModelElement *> XmlModelElement::children(int typeId, bool recursive) const
{
    QList<XmlModelElement *> foundChildren;
    XmlModelElementType *modelType = modelsFactory()->typeBuilder()->type(typeId);
    foundChildren = children(modelType, recursive);
    return foundChildren;
}

QList<XmlModelElement *> XmlModelElement::children(XmlModelElementType *type, bool recursive) const
{
    QList<XmlModelElement *> foundChildren;
    GUARD(!type, return foundChildren)

    auto childs = childElements();
    for(XmlModelElement* element: childElements()){
        if(type->isTypeOf(element)){
            foundChildren.append(element);
        }
        if(recursive){
            foundChildren.append(element->children(type, true));
        }
    }
    return foundChildren;
}

QString XmlModelElement::toString() const
{
    return d_ptr->tag->name();
}

XmlAttributeBuilder *XmlModelElement::attributeBuilder() const
{
    return d_ptr->attributeBuilder;
}

XmlModelsFactory *XmlModelElement::modelsFactory() const
{
    return document()->modelsFactory();
}

}
#include "moc_xmlmodelelement.cpp"
