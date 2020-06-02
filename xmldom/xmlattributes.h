/*****************************************************************************
 * xmlattributes.h
 *
 * Created: 28.03.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <xmldom/xmldom_global.h>

namespace XmlDom {
class XmlTag;
class XmlModelDocument;
class XmlModelElement;
class XmlModelElementType;
class XmlAttributeBuilder;
FORWARD_DECLARE_PRIVATE(XmlBaseAttribute)
FORWARD_DECLARE_PRIVATE(XmlAttribute)
FORWARD_DECLARE_PRIVATE(XmlChildAttribute)
FORWARD_DECLARE_PRIVATE(XmlChildListAttribute)
FORWARD_DECLARE_PRIVATE(XmlReferenceAttribute)
FORWARD_DECLARE_PRIVATE(XmlReferenceListAttribute)

/*!
 * \brief The XmlBaseAttribute class
 */
class XMLDOM_EXPORT XmlBaseAttribute : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString namespaceUri READ namespaceUri CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    XmlBaseAttribute(XmlModelElement *modelElement, const QString &namespaceUri, const QString &name);
    ~XmlBaseAttribute();

    XmlTag *tag() const;
    XmlModelDocument *document() const;
    XmlModelElement *modelElement() const;
    QString namespaceUri() const;
    QString name() const;

private:
    friend class XmlDom::XmlAttributeBuilder;
    DECLARE_PRIVATE(XmlBaseAttribute)
};

/*!
 * \brief The XmlAttribute class presents text attribute of XMl element
 */
class XMLDOM_EXPORT XmlAttribute: public XmlBaseAttribute
{
    Q_OBJECT
    Q_PROPERTY(QVariant::Type type READ type CONSTANT)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)

public:
    XmlAttribute(XmlModelElement *modelElement, const QString &namespaceUri, const QString &name);
    ~XmlAttribute();

    QVariant::Type type() const;

    QVariant value() const;
    void setValue(const QVariant &value);

    /*!
     * \brief If property is enum use this function to set enumerator name,
     * if you want to save value as string
     * \param enumeratorName
     */
    void setEnumerator(const QString &enumeratorName);
    void setEnumerator(const QMetaObject &meta, const QString &enumeratorName);


    bool operator==(const XmlAttribute& other) const;
    bool operator==(XmlAttribute *other) const;
    QString toString() const;
    operator QString() const { return toString(); }
    friend QDebug operator<<(QDebug dbg, const XmlAttribute *attr)
    {
        dbg.nospace() << attr->toString();

        return dbg.space();
    }

    //Simplify value resolving
    template<typename T>
    T value() const
    {
        return value().value<T>();
    }

    template<typename T>
    void setValue(T *value)
    {
        setValue(QVariant::fromValue(value));
    }


signals:
    void valueChanged();

private:
    friend class XmlDom::XmlModelElement;
    DECLARE_PRIVATE(XmlAttribute)
};

/*!
 * \brief The XmlChildAttribute class
 */
class XMLDOM_EXPORT XmlChildAttribute : public XmlBaseAttribute
{
    Q_OBJECT
    Q_PROPERTY(int childType READ childType CONSTANT)
    Q_PROPERTY(QVariant value READ value NOTIFY valueChanged)
public:
    XmlChildAttribute(XmlModelElement *modelElement, XmlModelElementType *type);
    ~XmlChildAttribute();

    int childType();
    QVariant value();
    XmlModelElement *element();
    void setElement(XmlModelElement *element);

    template<class T>
    T element(){
        return qobject_cast<T>(element());
    }
signals:
    void valueChanged();

private:
    DECLARE_PRIVATE(XmlChildAttribute)
};

/*!
 * \brief The XmlChildListAttribute class
 */
class XMLDOM_EXPORT XmlChildListAttribute : public XmlBaseAttribute
{
    Q_OBJECT
    Q_PROPERTY(int childType READ childType CONSTANT)
    Q_PROPERTY(QVariantList values READ values NOTIFY valuesChanged)

public:
    XmlChildListAttribute(XmlModelElement *modelElement, XmlModelElementType *type);
    ~XmlChildListAttribute();

    int childType() const;
    QVariantList values();
    QList<XmlModelElement *> elements() const;
    QList<XmlModelElement *> elements(int typeId) const;

    void append(XmlModelElement* element);
    XmlModelElement* at(int index) const;
    int count() const;
    void clear();

    template<class T>
    QList<T> elements(){
        return toList<T>(elements());
    }
    template<class T>
    QList<T> elementForType(){
        return toList<T>(elements(qMetaTypeId<T>()));
    }

signals:
    void valuesChanged();

private:
    DECLARE_PRIVATE(XmlChildListAttribute)
};

/*!
 * \brief The XmlReferenceAttribute class creates reference (like pointer) to other element by given identifierName,
 * usally "id" attribute
 */
class XMLDOM_EXPORT XmlReferenceAttribute : public XmlBaseAttribute
{
    Q_OBJECT
    Q_PROPERTY(XmlDom::XmlModelElement* referenceElement READ referenceElement WRITE setReferenceElement NOTIFY referenceElementChanged)

public:
    XmlReferenceAttribute(XmlModelElement *modelElement, const QString &identifierName, const QString &namespaceUri, const QString &name);
    ~XmlReferenceAttribute();

    XmlDom::XmlModelElement *referenceElement();
    void setReferenceElement(XmlDom::XmlModelElement *value);

    template<class T>
    T referenceElement(){
        return qobject_cast<T>(referenceElement());
    }

signals:
    void referenceElementChanged();

private:
    DECLARE_PRIVATE(XmlReferenceAttribute)
};

/*!
 * \brief The XmlReferenceListAttribute class
 */
class XMLDOM_EXPORT XmlReferenceListAttribute : public XmlBaseAttribute
{
    Q_OBJECT
public:
    XmlReferenceListAttribute(XmlModelElement *modelElement, const QString &identifierName,
                              XmlModelElementType *type);
    ~XmlReferenceListAttribute();

    QList<XmlModelElement *> references() const;
    int count() const;
    bool contains(XmlModelElement* referenceElement) const;
    void append(XmlModelElement* referenceElement);
    void remove(XmlModelElement* referenceElement);

signals:
    void referencesChanged();

private:
    DECLARE_PRIVATE(XmlReferenceListAttribute)
};
}
Q_DECLARE_METATYPE(XmlDom::XmlBaseAttribute*)
Q_DECLARE_METATYPE(XmlDom::XmlAttribute*)
Q_DECLARE_METATYPE(XmlDom::XmlChildAttribute*)
Q_DECLARE_METATYPE(XmlDom::XmlChildListAttribute*)
Q_DECLARE_METATYPE(XmlDom::XmlReferenceAttribute*)
Q_DECLARE_METATYPE(XmlDom::XmlReferenceListAttribute*)

