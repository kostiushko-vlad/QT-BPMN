/*****************************************************************************
* xmldocument.h
*
* Created: 20.02.2019 2019 by Vladyslav Kostiushko
*

*
* This file may be distributed under the terms of GNU Public License version
* 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
* license should have been included with this file, or the project in which
 You may also find the details of GPL v3 at:
* http://www.gnu.org/licenses/gpl-3.0.txt
*
* If you have any questions regarding the use of this file, feel free to
* contact the author of this file, or the owner of the project in which

*****************************************************************************/
#pragma once
#include <QObject>
#include <xmldom/xmldom_global.h>

QT_FORWARD_DECLARE_CLASS(QIODevice)
QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)
QT_FORWARD_DECLARE_CLASS(QXmlStreamWriter)
namespace XmlDom {
struct AttributeName;
class XmlTag;
class BaseUndoCommand;
FORWARD_DECLARE_PRIVATE(XmlDocument)

/*!
 * \brief The XmlDocument class
 */
class XMLDOM_EXPORT XmlDocument : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName CONSTANT)
    Q_PROPERTY(XmlDom::XmlTag* rootTag READ rootTag CONSTANT)
    Q_PROPERTY(bool isModified READ isModified NOTIFY isModifiedChanged)

public:
    explicit XmlDocument(QObject *parent = nullptr);
    XmlDocument(const QString &filename, QObject *parent = nullptr);
    ~XmlDocument();

    /*!
     * \brief Current filename of the document
     */
    QString fileName();
    /*!
     * \brief if document is modified
     */
    bool isModified();
    void setIsModified(bool modified);

    /*!
     * \brief Uri to prefix map
     */
    QMap<QString, QString> namespaceUris() const;
    /*!
     * \brief Namespace for prefix
     */
    QString namespaceForPrefix(const QString &prefix);
    /*!
     * \brief Prefix for namespace
     */
    QString prefixForNamespace(const QString &ns);
    /*!
     * \brief Register namespaces for current document
     */
    virtual void addNamespace(const QString &namespaceUri, const QString &prefix = "");
    /*!
     * \brief Removes namespace from document
     */
    virtual void removeNamespace(const QString &namespaceUri);
    /*!
     * \brief nGenerates unique id, based on existings tag ids
     */
    virtual QString nextUniqueId(const QString &key);

    // Tag operations:
    /*!
     * \brief Root XmlTag of the document
     */
    XmlTag *rootTag();

    /*!
     * \brief Returns list of all containing XMLTags
     */
    QList<XmlTag *> tags() const;
    /*!
     * \brief Add XmlTag to the document
     */
    virtual void addTag(XmlTag *tag);

    /*!
     * \brief Remove tag from the document
     */
    virtual void removeTag(XmlTag *tag);

    /*!
     * \brief returns qualified name for tag, prefix:name
     */
    QString qualifiedName(XmlTag *tag);


     // Serialization:
    /*!
     * \brief Generate XML into QIODevice
     */
    bool generateXML(QIODevice *io);
    /*!
     * \brief Generate XML into QString
     */
    bool generateXML(QString *content);
    /*!
     * \brief Generate XML into QByteArray
     */
    bool generateXML(QByteArray *content);
    /*!
     * \brief Generate XMl into QXmlStreamWriter
     */
    virtual bool generateXML(QXmlStreamWriter &xml);

public slots:
    void load(const QString &fileName);
    bool load(QIODevice *io);
    virtual bool load(QXmlStreamReader &xml);

    // Virtual slots:
    bool save();
    virtual bool save(const QString &fileName);

signals:
    void documentChanged();
    void modelElementsChanged();
    void isModifiedChanged(bool modified);
    /**
     * @brief beginElementChange - this signal will be emitted just before some ElementChange will be made (see ElementChange)
     */
    void beginCommandExecute(int commandId, XmlTag *tag, const QVariant &value);

    /**
     * @brief endElementChange - this signal will be emitted just after some ElementChange has made (see ElementChange)
     */
    void endCommandExecute(int commandId, XmlTag *tag, const QVariant &value);


private:
    DECLARE_PRIVATE(XmlDocument)
};
}
Q_DECLARE_METATYPE(XmlDom::XmlDocument*)
