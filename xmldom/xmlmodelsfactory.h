/*****************************************************************************
 * xmlmodelsfactory.h
 *
 * Created: 29.05.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <xmldom/xmlmodeldocument.h>
#include <xmldom/xmlmodelelement.h>
#include <xmldom/xmlmodelelementtypebuilder.h>
#include <QObject>
#include <xmldom/xmldom_global.h>

namespace XmlDom {
class XmlTag;
class XmlModelElement;
FORWARD_DECLARE_PRIVATE(XmlModelsFactory)
class XMLDOM_EXPORT XmlModelsFactory : public QObject
{
    Q_OBJECT
public:
    explicit XmlModelsFactory(QObject *parent = nullptr);
    ~XmlModelsFactory();
    XmlDom::XmlModelElementTypeBuilder *typeBuilder();
    XmlDom::XmlTag *createTag(int typeId, XmlModelDocument *doc);
    XmlDom::XmlTag *createTag(XmlModelElementType *type, XmlModelDocument *doc);
    XmlDom::XmlTag *createTag(const QString namespaceUri, const QString &name, XmlModelDocument *doc);
    XmlDom::XmlModelElement *createModel(XmlModelDocument *doc,const QString namespaceUri, const QString &typeName, XmlDom::XmlModelElement *parent = nullptr);
    XmlDom::XmlModelElement *createModel(XmlDom::XmlTag *tag, XmlDom::XmlModelElement *parent = nullptr);
    /*!
     * \brief  Copies \param model to the given \param document, \note new copy of model has no parent
     * \return new copy of model
     */
    XmlDom::XmlModelElement *copyModel(XmlDom::XmlModelElement *model, XmlDom::XmlModelDocument *document);

    /*!
     * \brief Registers namespace and version to the engine
     */
    void registerNamespace(const QString &namespaceUri, const QString &prefix);
    QHash<QString, QString> registeredNamespaces() const;
public:
    template <class T>
    T* createInstanceOfModel(XmlModelDocument *doc, XmlDom::XmlModelElement *parent = nullptr){
        XmlDom::XmlTag *tag = createTag(qMetaTypeId<T*>(), doc);
        XmlDom::XmlModelElement *element = doc->findModelElement(tag);
        if(parent) {
            parent->appendChild(element);
        }
        return qobject_cast<T*>(element);
    }
    template <class T>
    XmlDom::XmlTag *createTag(XmlModelDocument *doc){
        XmlDom::XmlTag *tag = createTag(qMetaTypeId<T*>(), doc);
        return tag;
    }

protected:
    void init();
    virtual void registerNamespaces();
    virtual void registerTypes(XmlDom::XmlModelElementTypeBuilder *typeBuilder) = 0;

signals:
    void modelCreated(XmlDom::XmlModelElement *);

private:
    DECLARE_PRIVATE(XmlModelsFactory)
};
}
Q_DECLARE_METATYPE(XmlDom::XmlModelsFactory*)
