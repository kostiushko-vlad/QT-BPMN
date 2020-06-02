#include "xmlmodelelementtypebuilder.h"
#include "xmlmodelelement.h"
#include <QMap>
#include <QDebug>
namespace XmlDom {
// Private declaration
using namespace Internal;
namespace Internal {
class XmlModelElementTypePrivate
{
public:    
    int typeId;
    QString namespaceUri;
    QString typeName;

    // Contains inherited ids
    QList<int> parentTypeIds;
    void buildType();
    void initParentTypeIds(int t);
    XmlModelElementTypeBuilder *typeBuilder = nullptr;
};
class XmlModelElementTypeBuilderPrivate
{
public:
    QHash<QPair<QString, QString>, XmlModelElementType*> types;
};

}

XmlModelElementType::XmlModelElementType(int typeId, const QString &namespaceUri, const QString &typeName)
    : d_ptr(new XmlModelElementTypePrivate)
{
    d_ptr->typeId = typeId;
    d_ptr->namespaceUri = namespaceUri;
    d_ptr->typeName = typeName;
}

XmlModelElementType::~XmlModelElementType()
{

}

int XmlModelElementType::typeId() const
{
    return d_ptr->typeId;
}

QString XmlModelElementType::namespaceUri() const
{
    return d_ptr->namespaceUri;
}

QString XmlModelElementType::typeName() const
{
    return d_ptr->typeName;
}

bool XmlModelElementType::isTypeOf(int typeId) const
{
    XmlModelElementType *type = d_ptr->typeBuilder->type(typeId);
    if(!type) {
        // Check base classes indirect inheritance
        if(d_ptr->parentTypeIds.contains(typeId)) {
            return true;
        } else {
            qDebug()<<"Xml Type not found for type id " << typeId;
        }
    }
    return isTypeOf(type);
}

XmlModelElement *XmlModelElementType::newModelElementInstance(XmlTag *tag) const
{
    XmlModelElement *modelElement = nullptr;
    const QMetaObject *metaObj = QMetaType::metaObjectForType(typeId());
    if(metaObj){
        QObject *obj = metaObj->newInstance(Q_ARG(XmlDom::XmlTag*, tag));
        modelElement = qobject_cast<XmlModelElement*>(obj);
        if(!modelElement){
            qDebug() << "Constructor for type " << metaObj->className()
                     << "not found. Did you forget to mark it as Q_INVOKABLE";

        }
    } else {
        qDebug()<< "Type not found"<< metaObj->className();
    }

    return modelElement;
}

XmlModelElement *XmlModelElementType::newModelElementInstance(XmlDocument *document) const
{
    return newModelElementInstance(new XmlTag(namespaceUri(), typeName(), document));
}

bool XmlModelElementType::isTypeOf(XmlModelElement *element) const
{
    GUARD(!element, return false)

    XmlModelElementType *type = element->type();
    if(!type) {
        qDebug()<<"Xml Type not found for element " << element;
    }
    return isTypeOf(type);
}

bool XmlModelElementType::isTypeOf(XmlModelElementType *type) const
{
    GUARD(!type, return false)

    bool thisIsABaseClass = type->d_ptr->parentTypeIds.contains(typeId());
    bool thisIsADrivenClass = d_ptr->parentTypeIds.contains(type->typeId());
    return thisIsABaseClass || thisIsADrivenClass;
}

XmlModelElementTypeBuilder::XmlModelElementTypeBuilder()
        : d_ptr(new XmlModelElementTypeBuilderPrivate)
{

}

XmlModelElementTypeBuilder::~XmlModelElementTypeBuilder()
{
}

QList<XmlModelElementType *> XmlModelElementTypeBuilder::types() const
{
    return d_ptr->types.values();
}

XmlModelElementType *XmlModelElementTypeBuilder::type(int typeId) const
{
    XmlModelElementType *foundType = nullptr;
    for(XmlModelElementType *type: d_ptr->types) {
        if(type->typeId() == typeId) {
            foundType = type;
            break;
        }
    }
    return foundType;
}

XmlModelElementType *XmlModelElementTypeBuilder::type(XmlTag *tag) const
{
    return type(tag->namespaceUri(), tag->name());
}

XmlModelElementType *XmlModelElementTypeBuilder::type(const QString namespaceUri, const QString &typeName) const
{
    return d_ptr->types.value(qMakePair(namespaceUri, typeName), nullptr);
}

void XmlModelElementTypeBuilder::registerType(int typeId, const QString namespaceUri, const QString &typeName)
{
//    qDebug() << "Register type " << typeId << typeName << namespaceUri;
    auto elementType = new XmlModelElementType(typeId, namespaceUri, typeName);
    elementType->d_ptr->typeBuilder = this;
    d_ptr->types.insert(qMakePair(namespaceUri, typeName), elementType);
}

void XmlModelElementTypeBuilder::registerBaseClass(int typeId, int baseTypeId)
{
    XmlModelElementType *elementType = type(typeId);
    if(elementType) {
        elementType->d_ptr->parentTypeIds.append(baseTypeId);
    }
}

void XmlModelElementTypeBuilder::buildTypes()
{
    for(XmlModelElementType* type: d_ptr->types){
        type->d_ptr->buildType();
    }
}

// ----------------- XmlModelElementTypePrivate ----------
void XmlModelElementTypePrivate::buildType()
{
    parentTypeIds.clear();
    initParentTypeIds(typeId);
}

// Adds types recursivelly throught all parent types
void XmlModelElementTypePrivate::initParentTypeIds(int t)
{    
    parentTypeIds.append(t);
    const QMetaObject *metaObj = QMetaType::metaObjectForType(t);
    const QMetaObject *superClassObj = metaObj->superClass();
    int id = QMetaType::type(superClassObj->className());
    if (id != QMetaType::UnknownType) {
        initParentTypeIds(id);
    }
}

}

