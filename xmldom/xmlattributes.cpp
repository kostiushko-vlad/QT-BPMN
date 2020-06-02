#include "xmlattributes.h"
#include "xmlmodelelement.h"
#include "xmlmodeldocument.h"
#include "xmltag.h"
#include "xmlmodelelement.h"
#include "xmlmodelsfactory.h"
#include "xmlmodelelementtypebuilder.h"
#include <QMetaMethod>

namespace XmlDom {
// Private declaration
using namespace Internal;
namespace Internal {

// XmlBaseAttributePrivate
class XmlBaseAttributePrivate
{
public:
    XmlModelElement *modelElement = nullptr;
    QString namespaceUri;
    QString name;
};

// XmlAttributePrivate
class XmlAttributePrivate
{
public:
    QVariant::Type valueType = QVariant::Invalid;
    QString enumeratorName = "";
    const QMetaObject *metObject = nullptr;
    QString keyForEnumValue(const QMetaObject *metObject, int val);
    int valueForEnumKey(const QMetaObject *metaObj, const QString &key);
};

// XmlChildAttributePrivate
class XmlChildAttributePrivate
{
public:
    int childType;
};

// XmlChilListAttributePrivate
class XmlChildListAttributePrivate
{
public:
    int childType;
    bool initialized = false;

};

// XmlReferenceAttributePrivate
class XmlReferenceAttributePrivate
{
public:
    QString identifierName;
};

// XmlReferenceListAttributePrivate
class XmlReferenceListAttributePrivate
{
public:
    XmlModelElementType *type = nullptr;
    QString identifierName;

};
}

// XmlBaseAttribute
XmlBaseAttribute::XmlBaseAttribute(XmlModelElement *modelElement, const QString &namespaceUri, const QString &name)
    : QObject(modelElement), d_ptr(new Internal::XmlBaseAttributePrivate)
{
    d_ptr->modelElement = modelElement;
    d_ptr->namespaceUri = namespaceUri;
    d_ptr->name = name;
    setObjectName(name);
}

XmlBaseAttribute::~XmlBaseAttribute()
{

}
XmlModelElement *XmlBaseAttribute::modelElement() const
{
    return d_ptr->modelElement;
}

XmlTag *XmlBaseAttribute::tag() const
{
    return d_ptr->modelElement ? d_ptr->modelElement->tag() : nullptr;
}

XmlModelDocument *XmlBaseAttribute::document() const
{
    return tag() ? qobject_cast<XmlModelDocument*>(tag()->document())
                 : nullptr;
}

QString XmlBaseAttribute::namespaceUri() const
{
    return d_ptr->namespaceUri;
}

QString XmlBaseAttribute::name() const
{
    return d_ptr->name;
}


// XmlAttribute
XmlAttribute::XmlAttribute(XmlModelElement *modelElement, const QString &namespaceUri, const QString &name)
    : XmlBaseAttribute(modelElement,namespaceUri, name), d_ptr(new XmlAttributePrivate)
{

}

XmlAttribute::~XmlAttribute()
{

}

QVariant::Type XmlAttribute::type() const
{
    return d_ptr->valueType;
}

QVariant XmlAttribute::value() const
{
    QVariant value(d_ptr->valueType);
    QString tagValue = tag()->attributeValue({namespaceUri(), name()});
    if(d_ptr->enumeratorName != ""){
        int enumValue = d_ptr->valueForEnumKey(d_ptr->metObject ? d_ptr->metObject
                                                                : modelElement()->metaObject(), tagValue);
        value.setValue(enumValue);
    } else {
        value.setValue(tagValue);
    }
    return value;
}

void XmlAttribute::setValue(const QVariant &newVal)
{
    if(value() != newVal){
        QVariant oldVal = value();
        QString value = newVal.toString();
        if(d_ptr->enumeratorName != ""){
            // Save enum as string
            value = d_ptr->keyForEnumValue(d_ptr->metObject ? d_ptr->metObject
                                                            : modelElement()->metaObject(), newVal.toInt());
        }
        d_ptr->valueType = newVal.type();
        tag()->setAttribute({namespaceUri(), name()}, value);
    }
}

void XmlAttribute::setEnumerator(const QMetaObject &meta, const QString &enumeratorName)
{
    d_ptr->metObject = &meta;
    setEnumerator(enumeratorName);
}

void XmlAttribute::setEnumerator(const QString &enumeratorName)
{
    d_ptr->enumeratorName = enumeratorName;
}

bool XmlAttribute::operator==(const XmlAttribute &other) const
{
    return this == &other;
}
bool XmlAttribute::operator==(XmlAttribute *other) const
{
    return this->namespaceUri() == other->namespaceUri()
        && this->name() == other->name()
        && this->type() == other->type()
        && this->value() == other->value();
}

QString XmlAttribute::toString() const
{
    return value().toString();
}

QString XmlAttributePrivate::keyForEnumValue(const QMetaObject *metaObj, int val)
{
    const char *name = enumeratorName.toLatin1();
    int index = metaObj->indexOfEnumerator(name);
    QMetaEnum metaEnum = metaObj->enumerator(index);
    const char* key = metaEnum.valueToKey(val);
    return QString::fromLatin1(key);
}

int XmlAttributePrivate::valueForEnumKey(const QMetaObject *metaObj, const QString &key)
{
    int index = metaObj->indexOfEnumerator(enumeratorName.toLatin1());
    QMetaEnum metaEnum = metaObj->enumerator(index);
    int val = metaEnum.keyToValue(key.toLatin1());
    return val;
}

// XmlChildAttribute
XmlChildAttribute::XmlChildAttribute(XmlModelElement *modelElement, XmlModelElementType *type)
    :XmlBaseAttribute(modelElement, type->namespaceUri(), type->typeName()), d_ptr(new XmlChildAttributePrivate)
{
    d_ptr->childType = type->typeId();
}

XmlChildAttribute::~XmlChildAttribute()
{

}

int XmlChildAttribute::childType()
{
    return d_ptr->childType;
}

QVariant XmlChildAttribute::value()
{
    return QVariant::fromValue(element());
}

XmlModelElement *XmlChildAttribute::element()
{
    XmlModelElementType *modelType = modelElement()->document()->modelsFactory()->typeBuilder()->type(d_ptr->childType);
    XmlModelElement *element = findOr(modelElement()->childElements(), nullptr, [=](XmlModelElement* element){
        return modelType->isTypeOf(element);
    });
    if(!element){
        auto elementTag = new XmlTag(modelType->namespaceUri(), modelType->typeName(), document());
        element = document()->findModelElement(elementTag);
        modelElement()->appendChild(element);
    }
    return element;
}

void XmlChildAttribute::setElement(XmlModelElement *element)
{
    modelElement()->removeChild(this->element());
    modelElement()->appendChild(element);
}

// XmlChildListAttribute
XmlChildListAttribute::XmlChildListAttribute(XmlModelElement *modelElement, XmlModelElementType *type)
    : XmlBaseAttribute(modelElement, type->namespaceUri(), type->typeName()), d_ptr(new XmlChildListAttributePrivate)
{
    d_ptr->childType = type->typeId();
}


XmlChildListAttribute::~XmlChildListAttribute()
{

}

int XmlChildListAttribute::childType() const
{
    return d_ptr->childType;
}

QVariantList XmlChildListAttribute::values()
{
    return toList<QVariant>(elements(), [](XmlModelElement *modelElement)->QVariant {
        return QVariant::fromValue(modelElement);
    });
}

QList<XmlModelElement *> XmlChildListAttribute::elements() const
{
    return elements(d_ptr->childType);
}

QList<XmlModelElement *> XmlChildListAttribute::elements(int typeId) const
{
    return modelElement()->children(typeId);
}

void XmlChildListAttribute::append(XmlModelElement *element)
{
    modelElement()->appendChild(element);
    emit valuesChanged();
}

XmlModelElement *XmlChildListAttribute::at(int index) const
{
    return modelElement()->childAt(index);
}

int XmlChildListAttribute::count() const
{
    return elements().count();
}

void XmlChildListAttribute::clear()
{
    for(XmlModelElement *e : elements()){
        modelElement()->removeChild(e);
    }
}

XmlReferenceAttribute::XmlReferenceAttribute(XmlModelElement *modelElement, const QString &identifierName,
                                             const QString &namespaceUri, const QString &name)
    : XmlBaseAttribute(modelElement, namespaceUri, name), d_ptr(new XmlReferenceAttributePrivate)
{
    d_ptr->identifierName = identifierName;
}

XmlReferenceAttribute::~XmlReferenceAttribute()
{

}
XmlModelElement *findElementByAttributeIdentifier(const QList<XmlModelElement *> &elements,
                                                  const QString &identifierName, const QString &lookUpIdentifier) {
    return findOr(elements, nullptr, [=](XmlModelElement* element){
        QString currentId = element->tag()->attributeValue(identifierName);
        return currentId == lookUpIdentifier;
    });
}
XmlModelElement *XmlReferenceAttribute::referenceElement()
{
    QString referenceId = tag()->attributeValue({namespaceUri(), name()});
    return findElementByAttributeIdentifier(document()->modelElements(), d_ptr->identifierName, referenceId);
}

void XmlReferenceAttribute::setReferenceElement(XmlModelElement *value)
{
    QString referenceValue = value->tag()->attributeValue(d_ptr->identifierName);
    tag()->setAttribute({namespaceUri(), name()}, referenceValue);
}

// XmlReferenceListAttribute
XmlReferenceListAttribute::XmlReferenceListAttribute(XmlModelElement *modelElement, const QString &identifierName, XmlModelElementType *type)
    : XmlBaseAttribute(modelElement, type->namespaceUri(), type->typeName()), d_ptr(new XmlReferenceListAttributePrivate)
{
    d_ptr->type = type;
    d_ptr->identifierName = identifierName;

}

XmlReferenceListAttribute::~XmlReferenceListAttribute()
{

}

QList<XmlModelElement *> XmlReferenceListAttribute::references() const
{
    // Get all children of type
    QList<XmlModelElement *> refElements = modelElement()->children(d_ptr->type);

    // Resolved model elemets by reference
    QList<XmlModelElement *> modelElements;
    for(XmlModelElement *element: refElements) {
        XmlTag *tag = element->tag();
        // Get identifier value
        QString identifier = tag->textContent();

        // Find other element with identifierId and value
        XmlModelElement *refElement = findElementByAttributeIdentifier(document()->modelElements(), d_ptr->identifierName, identifier);

        // Add to found element to resolved list
        modelElements.append(refElement);
    }
    return modelElements;
}
int XmlReferenceListAttribute::count() const
{
    return modelElement()->children(d_ptr->type).count();
}

void XmlReferenceListAttribute::append(XmlModelElement *refElement)
{
    XmlTag *referenceTag = modelElement()->modelsFactory()->createTag(d_ptr->type, document());
    XmlModelElement *referenceModel = document()->findModelElement(referenceTag);
    QString identifierValue = refElement->tag()->attributeValue(d_ptr->identifierName);
    if(identifierValue.isEmpty()) {
        qDebug() << "Reference cannot be created, because reference element has no attribute"
                  << d_ptr->identifierName << "to bind";
        return;
    }
    referenceTag->setTextContent(identifierValue);
    modelElement()->appendChild(referenceModel);
    emit referencesChanged();
}

bool XmlReferenceListAttribute::contains(XmlModelElement *key) const
{
    return modelElement()->children(d_ptr->type).contains(key);
}

void XmlReferenceListAttribute::remove(XmlModelElement *refElement)
{
    QList<XmlModelElement *> refElements = modelElement()->children(d_ptr->type);
    for(XmlModelElement *element: refElements) {
        QString identifierValue = element->tag()->textContent();
        QString refElementIdValue = refElement->tag()->attributeValue(d_ptr->identifierName);
        if(identifierValue == refElementIdValue) {
            modelElement()->removeChild(element);
            emit referencesChanged();
        }
    }
}

}


