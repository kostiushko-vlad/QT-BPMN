/*****************************************************************************
 * xmlmodeldocument.h
 *
 * Created: 15.01.2020 2020 by Vladyslav Kostiushko
 *

 *
 *****************************************************************************/
#pragma once
#include <xmldom/xmldocument.h>
#include <QObject>
#include <xmldom/xmldom_global.h>

namespace XmlDom {
class XmlModelElement;
class XmlBaseAttribute;
class XmlModelsFactory;
class XmlModelElementTypeBuilder;
FORWARD_DECLARE_PRIVATE(XmlModelDocument)
class XMLDOM_EXPORT XmlModelDocument : public XmlDocument
{
    Q_OBJECT
    Q_PROPERTY(XmlDom::XmlModelElement* rootElement READ rootElement CONSTANT)

public:
    explicit XmlModelDocument(XmlModelsFactory *modelsFactory, QObject *parent = nullptr);
    XmlModelDocument(const QString &filename, XmlModelsFactory *modelsFactory, QObject *parent = nullptr);
    ~XmlModelDocument();

    /*!
     * \brief Root model element of the document
     */
    XmlModelElement* rootElement();

    /*!
     * \brief Returns list of all containing Model Elements
     */
    QList<XmlModelElement *> modelElements() const;

    /*!
     * \brief XmlModelsFactory instance of models factory for current document
     * \return
     */
    XmlModelsFactory *modelsFactory();

    // Handle tag operations:
    virtual void addTag(XmlTag *tag);
    virtual void removeTag(XmlTag *tag);


public slots:
    /*!
     * \brief Find model element for XmlTag
     */
    XmlModelElement *findModelElement(XmlTag *tag);
    /*!
     * \brief Override loading, initialize model elements after
     * XmlDocument is loaded
     */
    virtual bool load(QXmlStreamReader &xml);

protected:
    /*!
     * \brief Set factory for resolving Model Elements
     */
    void setModelsFactory(XmlModelsFactory *modelsFactory);

private:
    DECLARE_PRIVATE(XmlModelDocument)
};
}
Q_DECLARE_METATYPE(XmlDom::XmlModelDocument*)
