#pragma once
#include <xmldom/xmltag.h>
#include <QObject>
#include <QDebug>
#include <xmldom/xmldom_global.h>

namespace XmlDom {
class XmlModelsFactory;
class XmlModelElement;
class XmlModelElementType;
class XmlModelElementTypeBuilder;
FORWARD_DECLARE_PRIVATE(XmlModelElementType)
FORWARD_DECLARE_PRIVATE(XmlModelElementTypeBuilder)

/*!
 * \brief The XmlModelElementType class
 */
class XMLDOM_EXPORT XmlModelElementType
{
public:
    XmlModelElementType(int typeId, const QString &namespaceUri, const QString &typeName);
    ~XmlModelElementType();

    int typeId() const;
    QString namespaceUri() const;
    QString typeName() const;
    /*!
     * \brief Looks for inheritance in both ways
     */
    bool isTypeOf(int typeId) const;
    bool isTypeOf(XmlModelElement* element) const;
    bool isTypeOf(XmlModelElementType* element) const;
    template<class T> bool isTypeOf() const {
        return isTypeOf(qMetaTypeId<T*>());
    }

    /*!
     * \brief Creates XmlModelElement based ob XmlTag
     */
    XmlModelElement *newModelElementInstance(XmlTag *tag) const;
    /*!
     * \brief Creates XmlModelElement and empty XmlTag
     */
    XmlModelElement *newModelElementInstance(XmlDocument *document) const;
    template<class T> T *newModelElementInstance(XmlTag *tag) const {
        return qobject_cast<T*>(newModelElementInstance(tag));
    }
    template<class T> T *newModelElementInstance(XmlDocument *document) const {
        return qobject_cast<T*>(newModelElementInstance(document));
    }

private:
    DECLARE_PRIVATE(XmlModelElementType)
    friend class XmlDom::XmlModelElementTypeBuilder;
};

/*!
 * \brief The XmlModelElementTypeBuilder class
 */
class XMLDOM_EXPORT XmlModelElementTypeBuilder
{
public:
    XmlModelElementTypeBuilder();
    ~XmlModelElementTypeBuilder();

    // Find types
    QList<XmlModelElementType *> types() const;
    XmlModelElementType *type(int typeId) const;
    XmlModelElementType *type(XmlTag* tag) const;
    XmlModelElementType *type(const QString namespaceUri, const QString &typeName) const;
    template<class T> XmlModelElementType* type(){
        return type(qMetaTypeId<T*>());
    }

    // Register types
    void registerType(int typeId, const QString namespaceUri, const QString &typeName);
    template<class T> void registerType(const QString namespaceUri, const QString &typeName) {
        qRegisterMetaType<T*>(T::staticMetaObject.className());
        registerType(qMetaTypeId<T*>(), namespaceUri, typeName);
    }
    void registerBaseClass(int typeId, int baseTypeId);
    template<class Driven, class Base> void registerBaseClass() {
        registerBaseClass(qRegisterMetaType<Driven*>(), qMetaTypeId<Base*>());
    }

    /*!
     * \brief Call this method build registered types, and update info about them
     */
    void buildTypes();

private:
    DECLARE_PRIVATE(XmlModelElementTypeBuilder)
};
}
