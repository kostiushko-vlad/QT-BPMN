/*****************************************************************************
* xmltag.h
*
* Created: 20.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <QObject>
#include <QQmlListProperty>
#include <xmldom/xmlattributebuilder.h>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <xmldom/xmldom_global.h>

namespace XmlDom {
class XmlBaseAttribute;
class XmlDocument;
FORWARD_DECLARE_PRIVATE(XmlTag)

/*!
* \brief Reperesents attribute indentifier, namepsaceUri + name
*/
struct AttributeName
{
    QString namespaceUri;
    QString name;

    bool operator==(const AttributeName &other) const
    {
        return this->name == other.name && this->namespaceUri == other.namespaceUri;
    }
};
// Overloading < operator, to be able to use struct as key map
bool operator<(const AttributeName &a, const AttributeName &b);
inline uint qHash(const AttributeName &a);
/*!
 * \brief The XmlTag class represents one element in the XML document tree.
 */
class XMLDOM_EXPORT XmlTag : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString namespaceUri READ namespaceUri WRITE setNamespaceUri NOTIFY namespaceUriChanged)
    Q_PROPERTY(XmlDom::XmlDocument* document READ document WRITE setDocument NOTIFY documentChanged)
    Q_PROPERTY(XmlDom::XmlTag* parentTag READ parentTag WRITE setParentTag NOTIFY parentTagChanged)
    Q_PROPERTY(QString textContent READ textContent WRITE setTextContent NOTIFY textContentChanged)

public:
    XmlTag(const QString &namespaceUri, const QString &name, XmlDocument *document);
    XmlTag(XmlTag *other, XmlDocument *newDocument);
    ~XmlTag();

    /*!
     * \brief Namespace for tag
     */
    QString namespaceUri();
    void setNamespaceUri(QString value);

    /*!
     * \brief Name of the tag
     */
    QString name();
    void setName(QString value);

    /*!
     * \brief Owner document
     */
    XmlDocument *document();
    /*!
     * \brief Only the XmlDocument can set refence for an XML tag
     */
    void setDocument(XmlDocument* value);

    // Parent handling:
    /*!
     * \brief Parent XmlTag
     */
    XmlTag *parentTag();

    /*!
     * \brief Set parent tag
     */
    void setParentTag(XmlTag* value);

    /*!
     * \brief index in parent tag
     */
    int index() const;

    /*!
     * \brief Text content of this tag
     */
    QString textContent() const;
    void setTextContent(const QString &value);

    // Attributes handling:
    /*!
     * \brief List of attributes
     */
    QList<AttributeName> attributes() const;
    /*!
     * \brief Add attribute or replace existing one
     * \param attribute
     */
    void setAttribute(const AttributeName &name, const QString &value);

    /*!
     * \brief Index of attribute in the list
     * \param name
     * \return
     */
    int attributeIndex(const AttributeName &name) const;

    /*!
     * \brief Attribute for given name and namespaceUri
     */
    QString attributeValue(const AttributeName &name);
    /*!
     * \brief Attribute value without namespace
     */
    QString attributeValue(const QString &name);

    /*!
     * \brief Remove attribute from this Tag
     */
    void removeAttribute(const AttributeName &name);

    // Children handling:
    /*!
     * \brief List of children XmlTags
     */
    QList<XmlTag *> childTags() const;
    /*!
     * \brief Returns true if tag has children with given name
     */
    bool hasChild(const QString &namespaceUri, const QString &tagName) const;

    /*!
     * \brief Find first child  for give namespace and tagName
     */
    XmlTag *child(const QString &namespaceUri, const QString &tagName) const;

    /*!
     * \brief Find all children for give namespace and tagName
     */
    QList<XmlTag *> children(const QString &namespaceUri, const QString &tagName) const;

    /*!
     * \brief child at index
     */
    XmlTag *child(int index) const;

    /*!
     * \brief index of children XmlTag
     */
    int childIndex(const XmlTag *child) const;

    /*!
     * \brief Append XmlTag as child
     */
    void appendChild(XmlTag *tag);

    /*!
     * \brief Remove child XmlTag
     */
    void removeChild(XmlTag *child);

    /*!
     * \brief clearChildren
     */
    void clearChildren();

    /*!
     * \brief Insert XmlTag for index
     */
    void insertChild(int index, XmlTag *child);

    /*!
     * \brief moveChild
     */
    void moveChild(int oldPos, int newPos);


    // Serialization handling:
    /*!
     * \brief Serializes XmlTag to Xml
     * \param xml
     */
    virtual void readXml(QXmlStreamReader &xml) ;

    /*!
     * \brief Read XmlTag from XML
     * \param xml
     */
    virtual void writeXml(QXmlStreamWriter &xml) ;

signals:
    void nameChanged();
    void namespaceUriChanged();
    void documentChanged();
    void parentTagChanged();
    void textContentChanged();
    void attributesChanged();
    void attributeChanged(const AttributeName &attribute);
    void attributeRemoved(const AttributeName &attribute);
    void childTagsChanged();
    void childAdded(XmlTag *child);
    void childRemoved(XmlTag *child);

private:
    friend class XmlDom::XmlDocument;
    DECLARE_PRIVATE(XmlTag)
};

}
Q_DECLARE_METATYPE(XmlDom::XmlTag*)
