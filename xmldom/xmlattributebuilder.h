#pragma once
#include <xmldom/xmlattributes.h>
#include <QObject>
#include <xmldom/xmldom_global.h>

namespace XmlDom {
class XmlModelElement;
FORWARD_DECLARE_PRIVATE(XmlAttributeBuilder)
/*!
 * \brief The XmlAttributeBuilder class helps to build different attribute types
 */
class XMLDOM_EXPORT XmlAttributeBuilder
{
public:
    explicit XmlAttributeBuilder(XmlModelElement *modelElement);
    ~XmlAttributeBuilder();

    /*!
     * \brief Attribute builder notifies that new attribute is created
     * and should be added to the model
     */
    typedef std::function<void (XmlBaseAttribute *)> AttributeListener;
    void setListener(const AttributeListener &listener);

    /*!
     * \brief Handling ModelElement
     */
    XmlModelElement *modelElement() const;

    /*!
     * \brief Create simple "name:value" XmlAttirbute
     */
    XmlAttribute *createAttribute(const QString &namespaceUri, const QString &name);

    /*!
     * \brief Create reference attibute to other model element by identifierName "otherElement:identifierName"
     */
    XmlReferenceAttribute *createReferenceAttribute(const QString &identifierName, const QString &namespaceUri, const QString &name);

    /*!
     * \brief Create list of reference to other model elements
     */
    XmlReferenceListAttribute *createReferenceListAttribute(int typeId, const QString &identifierName);

    /*!
     * \brief Create children model element as attribute
     */
    XmlChildAttribute *createChildAttribute(int typeId);

    /*!
     * \brief Create list of child model elements with type
     */
    XmlChildListAttribute *createChildListAttribute(int typeId);

    // Template methods to simplify use for Q_PROPERTY
    template <typename Func1>
    XmlAttribute *createAttribute(const QString &name, const typename QtPrivate::FunctionPointer<Func1>::Object *receiver, Func1 slot) {
        return createAttribute("", name, receiver, slot);
    }

    template <typename Func1>
    XmlAttribute *createAttribute(const QString &namespaceUri, const QString &name, const typename QtPrivate::FunctionPointer<Func1>::Object *receiver, Func1 slot) {
        XmlAttribute *attr = createAttribute(namespaceUri, name);
        QObject::connect(attr, &XmlAttribute::valueChanged, receiver, slot);
        return attr;
    }

    template <typename Func1>
    XmlReferenceAttribute *createReferenceAttribute(const QString &identifierName, const QString &name,
                                                    const typename QtPrivate::FunctionPointer<Func1>::Object *receiver, Func1 slot) {
        return createReferenceAttribute(identifierName, "", name, receiver, slot);
    }

    template <typename Func1>
    XmlReferenceAttribute *createReferenceAttribute(const QString &identifierName, const QString &namespaceUri,const QString &name,
                                                    const typename QtPrivate::FunctionPointer<Func1>::Object *receiver, Func1 slot) {
        XmlReferenceAttribute *attr = createReferenceAttribute(identifierName, namespaceUri, name);
        QObject::connect(attr, &XmlReferenceAttribute::referenceElementChanged, receiver, slot);
        return attr;
    }

    template <class T, typename Func1>
    XmlReferenceListAttribute *createReferenceListAttribute(const QString &identifierName, const typename QtPrivate::FunctionPointer<Func1>::Object *receiver, Func1 slot) {
        XmlReferenceListAttribute *attr = createReferenceListAttribute(qMetaTypeId<T*>(), identifierName);
        QObject::connect(attr, &XmlReferenceListAttribute::referencesChanged, receiver, slot);
        return attr;
    }

    template <class T, typename Func1>
    XmlChildAttribute *createChildAttribute(const typename QtPrivate::FunctionPointer<Func1>::Object *receiver, Func1 slot) {
        XmlChildAttribute *attr = createChildAttribute(qMetaTypeId<T*>());
        QObject::connect(attr, &XmlChildAttribute::valueChanged, receiver, slot);
        return attr;
    }

    template <class T, typename Func1>
    XmlChildListAttribute *createChildListAttribute(const typename QtPrivate::FunctionPointer<Func1>::Object *receiver, Func1 slot) {
        XmlChildListAttribute *attr = createChildListAttribute(qMetaTypeId<T*>());
        QObject::connect(attr, &XmlChildListAttribute::valuesChanged, receiver, slot);
        return attr;
    }

private:
    DECLARE_PRIVATE(XmlAttributeBuilder)
};
}
