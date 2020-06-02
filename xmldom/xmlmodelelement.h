#pragma once
#include <xmldom/xmldom_global.h>
#include <QObject>
#include <QQmlListProperty>
#include <xmldom/xmlattributebuilder.h>
namespace XmlDom {
class XmlTag;
class XmlModelDocument;
class XmlModelsFactory;
class XmlBaseAttribute;
class XmlAttributeBuilder;
class XmlModelElementType;
FORWARD_DECLARE_PRIVATE(XmlModelElement)
/*!
 * \brief The XmlModelElement class
 */
class XMLDOM_EXPORT XmlModelElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(XmlDom::XmlTag* tag READ tag CONSTANT)
    Q_PROPERTY(XmlDom::XmlModelElement* parentElement READ parentElement NOTIFY parentElementChanged)
    Q_PROPERTY(XmlDom::XmlModelDocument* document READ document CONSTANT)
public:
    XmlModelElement(XmlDom::XmlTag* tag);
    ~XmlModelElement();

    /*!
     * \brief tag
     */
    XmlDom::XmlTag *tag() const;

    /*!
     * \brief Returns corresponding XmlModelsFactory for this context
     */
    XmlModelsFactory *modelsFactory() const;

    /*!
     * \brief parentElement
     */
    XmlDom::XmlModelElement *parentElement() const;

    /*!
     * \brief document
     */
    XmlModelDocument *document() const;

    /*!
     * \brief Returns XmlAttributeBuilder used for creating attributes
     */
    XmlAttributeBuilder *attributeBuilder() const;

    /*!
     * \brief Class that describes model element type,
     * it is like QMetaObject for Qt objects.
     * \return
     */
    XmlDom::XmlModelElementType *type() const;

    /*!
     * \brief attributes
     */
    QList<XmlBaseAttribute *> attributes() const;
    /*!
     * \brief findAttribute
     */
    XmlBaseAttribute *findAttribute(const QString &namespaceUri, const QString &name) const;

    /*!
     * \brief clearAttributes
     */
    void clearAttributes();

    // Functions for handling extension
    QList<XmlModelElement *> childElements() const;
    QList<XmlModelElement *> children(int typeId, bool recursive = false) const;
    QList<XmlModelElement *> children(XmlModelElementType *type, bool recursive = false) const;
    //QList<XmlTag *> children(XmlModelElementType *type) const;
    XmlModelElement *childAt(int) const;
    int childIndex(const XmlModelElement *child) const;

    int index() const;
    int childCount() const;
    void appendChild(XmlModelElement *child);
    void insertChild(int index, XmlModelElement *child);
    void removeChild(XmlModelElement *child);
    void moveChild(int oldPos, int newPos);
    void clearChildren();
    template<class T>
    QList<T*> children(bool recursive = false) const{
        return toList<T*>(children(qMetaTypeId<T*>(), recursive));
    }
    template<class T>
    T* child(bool recursive = false) const{
        QList<T*> elementList = children<T>(recursive);
        if(!elementList.isEmpty())
            return elementList.first();
        return nullptr;
    }

    virtual QString toString() const;


protected:
    /*!
     * \brief Add attribute to model
     */
    virtual void setAttribute(XmlBaseAttribute *attribute);
    virtual void finilizeCreation();

signals:
    void parentElementChanged();
    void attributesChanged();
    void childrenChanged();

private:
    friend class XmlDom::XmlModelDocument;
    DECLARE_PRIVATE(XmlModelElement)
};
}
Q_DECLARE_METATYPE(XmlDom::XmlModelElement*)
