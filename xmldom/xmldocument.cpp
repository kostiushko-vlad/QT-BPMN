#include "xmldocument.h"
#include "xmlmodelelement.h"
#include "xmlmodelsfactory.h"
#include <QFile>
namespace XmlDom{
// Private declaration
using namespace Internal;
namespace Internal {
class XmlDocumentPrivate
{
public:
    XmlDocumentPrivate(XmlDocument *doc):q(doc){}
    QString fileName;
    XmlTag *rootTag = nullptr;
    QMap<QString, QString> namespaceUris;
    QHash<QString, int> nextIdHash;
    QString lastError;
    bool isModified = false;

    // Model elements
    QList<XmlTag*> tags;
private:
    XmlDocument *q = nullptr;
};
}
XmlDocument::XmlDocument(QObject *parent)
    : QObject(parent), d_ptr(new XmlDocumentPrivate(this))
{
}

XmlDocument::XmlDocument(const QString &filename, QObject *parent)
    : QObject(parent), d_ptr(new XmlDocumentPrivate(this))
{
    load(filename);
}

XmlDocument::~XmlDocument()
{
    if(rootTag()) {
        delete d_ptr->rootTag;
    }
    // Delete tags without connections
//    QList<XmlTag*> removeTags = tags();
//    for(XmlTag *tag: removeTags) {
//        delete tag;
//    }
    d_ptr->tags.clear();
}

QList<XmlTag *> XmlDocument::tags() const
{
    return d_ptr->tags;
}

void XmlDocument::addTag(XmlTag *tag)
{
    if(!d_ptr->tags.contains(tag)) {
        d_ptr->tags.append(tag);
    }
}

void XmlDocument::removeTag(XmlTag *tag)
{
    d_ptr->tags.removeAll(tag);
}

QString XmlDocument::fileName()
{
    return d_ptr->fileName;
}

QMap<QString, QString> XmlDocument::namespaceUris() const
{
    return d_ptr->namespaceUris;
}

void XmlDocument::addNamespace(const QString &namespaceUri, const QString &prefix)
{
    d_ptr->namespaceUris.insert(namespaceUri, prefix);
}

void XmlDocument::removeNamespace(const QString &namespaceUri)
{
    d_ptr->namespaceUris.remove(namespaceUri);
}

QString XmlDocument::nextUniqueId(const QString &key)
{
    QString name;
    bool bFound = false;
    int id = 0;
    while (true) {
        id = d_ptr->nextIdHash.value(key, 0) + 1;
        d_ptr->nextIdHash[key] = id;
        bFound = false;
        name = QString::fromLatin1("%1_%2").arg(key).arg(id);

        // Check duplicate
        for(XmlTag *tag : d_ptr->tags) {
            if (tag->attributeValue({"","id"}) == name) {
                bFound = true;
                break;
            }
        }
        if (!bFound) {
            break;
        }
    }
    return name;
}

XmlTag *XmlDocument::rootTag()
{
    return d_ptr->rootTag;
}

bool XmlDocument::isModified()
{
    return d_ptr->isModified;
}

void XmlDocument::setIsModified(bool value)
{
    if(d_ptr->isModified != value) {
        d_ptr->isModified = value;
        emit isModifiedChanged(value);
    }
}

QString XmlDocument::namespaceForPrefix(const QString &prefix)
{
    return d_ptr->namespaceUris.key(prefix, "");
}

QString XmlDocument::prefixForNamespace(const QString &ns)
{
    return d_ptr->namespaceUris.value(ns);
}

QString XmlDocument::qualifiedName(XmlTag *tag)
{
    GUARD(!tag, return "")

    QString qualifiedName = prefixForNamespace(tag->namespaceUri()) + ":" + tag->name();
    return qualifiedName;
}

bool XmlDocument::save(const QString &fileName)
{
    QString name(fileName);
    bool ok = true;

    QFile file(name);
    if (file.open(QIODevice::WriteOnly)) {
        ok = generateXML(&file);
        if (ok) {
            d_ptr->fileName = name;
            setIsModified(false);
        }
        file.close();
        if (!ok) {
            d_ptr->lastError = tr("Cannot save XML to the file %1.").arg(fileName);
        }
    } else {
        ok = false;
        d_ptr->lastError = tr("Cannot open file %1.").arg(fileName);
    }

    return ok;
}

bool XmlDocument::generateXML(QIODevice *io)
{
    QXmlStreamWriter xml(io);
    return generateXML(xml);
}

bool XmlDocument::generateXML(QString *content)
{
    QXmlStreamWriter xml(content);
    return generateXML(xml);
}

bool XmlDocument::generateXML(QByteArray *content)
{
    QXmlStreamWriter xml(content);
    return generateXML(xml);
}

bool XmlDocument::generateXML(QXmlStreamWriter &xml)
{
    xml.setAutoFormatting(true);
    if(rootTag()){
        // Define namespaces
        for(const QString &namespaceUri: namespaceUris().keys()){
            xml.writeNamespace(namespaceUri, prefixForNamespace(namespaceUri));
        }

        // Write root tag
        rootTag()->writeXml(xml);
    }
    return !xml.hasError();
}

bool XmlDocument::save()
{
    return save(d_ptr->fileName);
}

void XmlDocument::load(const QString &fileName)
{
    d_ptr->fileName = fileName;
    if (QFile(d_ptr->fileName).exists()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            if (load(&file)) {
            }
        }
        QString error = file.errorString();
    }
}

bool XmlDocument::load(QIODevice *io)
{
    QXmlStreamReader xml(io);
    return load(xml);
}

bool XmlDocument::load(QXmlStreamReader &xml)
{
    while (!xml.atEnd()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }

        if (token == QXmlStreamReader::StartElement) {
            // Get and add namespaces
            QXmlStreamNamespaceDeclarations ns = xml.namespaceDeclarations();
            for (int i = 0; i < ns.count(); ++i) {
                addNamespace(ns[i].namespaceUri().toString(), ns[i].prefix().toString());
            }
            // Init root tag
            QString namepaceUri = namespaceForPrefix(xml.prefix().toString());
            QString name = xml.name().toString();
            auto rootTag = new XmlTag(namepaceUri, name, this);
            d_ptr->rootTag = rootTag;
            rootTag->readXml(xml);
        }

        if (token == QXmlStreamReader::Invalid) {
            break;
        }
    }
    return true;
}
}

