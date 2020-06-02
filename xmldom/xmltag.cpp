#include "xmltag.h"
#include "xmldocument.h"
#include "xmlattributes.h"
#include "xmlattributebuilder.h"
#include "xmlmodelelementtypebuilder.h"
#include "xmlmodelelement.h"
#include "xmlmodelsfactory.h"
#include <QVariantMap>
#include <QDebug>
namespace XmlDom {
// LessThanComparable

using namespace Internal;
// Private declaration
namespace Internal {


class XmlTagPrivate
{
public:
    XmlTagPrivate(XmlTag *tag)
        :q(tag){}
    XmlDocument *document = nullptr;
    XmlTag *parentTag = nullptr;
    QString name;
    QString namespaceUri;
    QString textContent;
    QHash<AttributeName, QString> attributes;
    QList<XmlTag*> childTags;

private:
    XmlTag *q = nullptr;
};

}
XmlTag::XmlTag(const QString &namespaceUri, const QString &name, XmlDocument *document)
    : d_ptr(new Internal::XmlTagPrivate(this))
{
    d_ptr->namespaceUri = namespaceUri;
    d_ptr->name = name;
    setDocument(document);
}

XmlTag::XmlTag(XmlTag *other, XmlDocument *newDocument)
    : d_ptr(new Internal::XmlTagPrivate(this))
{
    d_ptr->namespaceUri = other->d_ptr->namespaceUri;
    d_ptr->name = other->d_ptr->name;
    d_ptr->attributes = other->d_ptr->attributes;
    auto atttr = d_ptr->attributes;

    setDocument(newDocument);
    for(XmlTag* child: other->d_ptr->childTags) {
        auto copyChild = new XmlTag(child, newDocument);
        copyChild->setParentTag(this);
        d_ptr->childTags.append(copyChild);
    }

}
XmlTag::~XmlTag()
{
    // Delete children
    for(XmlTag *tag: childTags()) {
        delete tag;
    }
    // Remove from parent child list
    if(d_ptr->parentTag){
        d_ptr->parentTag->d_ptr->childTags.removeAll(this);
        d_ptr->parentTag = nullptr;
    }
    // Remove from document
    if(d_ptr->document) {
        d_ptr->document->removeTag(this);
    }
}

QString XmlTag::namespaceUri()
{
    return d_ptr->namespaceUri;
}

void XmlTag::setNamespaceUri(QString value)
{
    PROPERTY_IMPLEMENTATION(namespaceUri)
}

QString XmlTag::name()
{
    return d_ptr->name;
}

void XmlTag::setName(QString value)
{
    PROPERTY_IMPLEMENTATION(name)
}

XmlDocument *XmlTag::document()
{
    return d_ptr->document;
}

void XmlTag::setDocument(XmlDocument *value)
{
    if (d_ptr->document != value) {
        // Remove tag from previous document
        if (d_ptr->document) {
            d_ptr->document->removeTag(this);
        }

        d_ptr->document = value;

        // Add tag to current document
        if (d_ptr->document) {
            d_ptr->document->addTag(this);
        }
    }
}

XmlTag *XmlTag::parentTag()
{
    return d_ptr->parentTag;
}

void XmlTag::setParentTag(XmlTag *value)
{
    PROPERTY_IMPLEMENTATION(parentTag)
}

QList<AttributeName> XmlTag::attributes() const
{
    return d_ptr->attributes.keys();
}

QString XmlTag::textContent() const
{
    return d_ptr->textContent;
}

void XmlTag::setTextContent(const QString &value)
{
    PROPERTY_IMPLEMENTATION(textContent)
}

QList<XmlTag *> XmlTag::childTags() const
{
    return d_ptr->childTags;
}

int XmlTag::attributeIndex(const AttributeName &name) const
{
    return d_ptr->attributes.keys().indexOf(name);
}

QString XmlTag::attributeValue(const AttributeName &name)
{
    return d_ptr->attributes.value(name);
}

QString XmlTag::attributeValue(const QString &name)
{
    return attributeValue({"", name});
}

void XmlTag::setAttribute(const AttributeName &name, const QString &value)
{
    GUARD(name.name.isEmpty(), return)

    d_ptr->attributes.insert(name, value);
    emit attributeChanged(name);
    emit attributesChanged();
}

void XmlTag::removeAttribute(const AttributeName &name)
{
    d_ptr->attributes.remove(name);
    emit attributeRemoved(name);
    emit attributesChanged();
}

bool XmlTag::hasChild(const QString &namespaceUri, const QString &tagName) const
{
    XmlTag *foundChild = child(namespaceUri, tagName);
    return foundChild;
}

XmlTag *XmlTag::child(const QString &namespaceUri, const QString &tagName) const
{
    XmlTag *foundChild = findOr(childTags(), nullptr, [=](XmlTag * tag){
        return tag->namespaceUri() == namespaceUri && tag->name() == tagName;
    });
    return foundChild;
}

QList<XmlTag *> XmlTag::children(const QString &namespaceUri, const QString &tagName) const
{
    QList<XmlTag *> foundChildren = filtered(childTags(), [=](XmlTag *tag){
        //qDebug() <<"Tag" << tag->namespaceUri() << tag->name() << "looking for" << namespaceUri <<tagName;
        return tag->namespaceUri() == namespaceUri && tag->name() == tagName;
    });
    return foundChildren;
}

XmlTag *XmlTag::child(int index) const
{
    return d_ptr->childTags.at(index);
}

int XmlTag::childIndex(const XmlTag *child) const
{
    return d_ptr->childTags.indexOf(const_cast<XmlTag*>(child));
}

int XmlTag::index() const
{
    return d_ptr->parentTag ? d_ptr->parentTag->childIndex(this): 0;
}

void XmlTag::appendChild(XmlTag *child)
{
    if(!d_ptr->childTags.contains(child)) {
        d_ptr->childTags.append(child);
        child->setParentTag(this);
        connect(child, &XmlTag::childAdded, this, &XmlTag::childAdded);
        connect(child, &XmlTag::childTagsChanged, this, &XmlTag::childTagsChanged);
        emit childAdded(child);
        emit childTagsChanged();
    }
}

void XmlTag::removeChild(XmlTag *child)
{
    if(d_ptr->childTags.contains(child)) {
        d_ptr->childTags.removeAll(child);
        child->setParentTag(nullptr);
        disconnect(child, &XmlTag::childAdded, this, &XmlTag::childAdded);
        connect(child, &XmlTag::childTagsChanged, this, &XmlTag::childTagsChanged);
        emit childRemoved(child);
        emit childTagsChanged();
    }
}

void XmlTag::clearChildren()
{
    if(childTags().count()) {
        for(XmlTag *tag: childTags()){
            //d_ptr->childTags.removeAll(tag);
            delete tag;
        }
        emit childTagsChanged();
    }
}

void XmlTag::insertChild(int index, XmlTag *child)
{
    if(!d_ptr->childTags.contains(child)) {
        if (index >= 0 && index < d_ptr->childTags.count()) {
            d_ptr->childTags.insert(index, child);
            child->setParentTag(this);
            emit childAdded(child);
            emit childTagsChanged();
        } else {
            appendChild(child);
        }
    }
}

void XmlTag::moveChild(int oldPos, int newPos)
{
    d_ptr->childTags.insert(newPos, d_ptr->childTags.takeAt(oldPos));
    emit childTagsChanged();
}

void XmlTag::readXml(QXmlStreamReader &xml)
{
    // Check errors but try to parse futher
    if(xml.hasError()) {
        qDebug()<< xml.errorString();
    }

    // Read and set attributes
    QXmlStreamAttributes attributes = xml.attributes();
    for (int i = 0; i < attributes.count(); ++i) {
        QString namespaceUri = attributes[i].namespaceUri().toString();
        QString key = attributes[i].name().toString();
        QString value = attributes[i].value().toString();
        d_ptr->attributes.insert(AttributeName{namespaceUri, key}, value);
    }

    // Read children states
    QXmlStreamReader::TokenType token = xml.readNext();
    while (token != QXmlStreamReader::EndElement) {
        if (token == QXmlStreamReader::Characters)
            d_ptr->textContent = xml.text().toString().trimmed();
        else if (token == QXmlStreamReader::StartElement) {
            QString namepaceUri = document()->namespaceForPrefix(xml.prefix().toString());
            QString name = xml.name().toString();
            XmlTag* childTag = new XmlTag(namepaceUri, name, document());
            // Add to child tag
            d_ptr->childTags.append(childTag);
            childTag->setParentTag(this);

            // Read content
            childTag->readXml(xml);
        } else if (token == QXmlStreamReader::Invalid) {
            qDebug() << "Error in reading XML "<< xml.error() << ":"
                     << xml.errorString();
            break;
        }

        token = xml.readNext();
    }
}

void XmlTag::writeXml(QXmlStreamWriter &xml)
{
    // Start tag
    xml.writeStartElement(namespaceUri(), name());

    // Write attributes
    for(AttributeName &name: d_ptr->attributes.keys()){
        xml.writeAttribute(name.namespaceUri, name.name, d_ptr->attributes[name]);
    }

    // Write text content
    if (d_ptr->textContent != "") {
        xml.writeCharacters(d_ptr->textContent);
    }

    // Write children
    for(XmlTag *tag: childTags()){
        tag->writeXml(xml);
    }

    // End tag
    xml.writeEndElement();
}

bool operator<(AttributeName a, AttributeName b)
{
    return std::tie(a.namespaceUri, a.name) < std::tie(b.namespaceUri, b.name);
}

uint qHash(const AttributeName &a)
{
    { return qHash(qMakePair(a.namespaceUri, a.name), 0xa03f); }
}

}

