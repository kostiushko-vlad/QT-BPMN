/*****************************************************************************
 * contextvariable.h
 *
 * Created: 11.04.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
namespace Xooo {
class ContextVariable;
XOOO_FORWARD_DECLARE_PRIVATE(ContextVariable)
class BPMN_LIBRARY_EXPORT ContextVariable : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(Contants::CollectionType collectionType READ collectionType WRITE setCollectionType NOTIFY collectionTypeChanged)


public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<ContextVariable>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_CONTEXT_VARIABLE);
    }

    Q_INVOKABLE ContextVariable(XmlDom::XmlTag *tag);
    ~ContextVariable();


    /*!
     * \brief name
     * \return
     */
    QString name() const;
    void setName(const QString &value);

    /*!
     * \brief parameterType
     * \return
     */
    QString type() const;
    void setType(const QString &value);

    /*!
     * \brief value
     * \return
     */
    QString value() const;
    void setValue(const QString &value);

    /*!
     * \brief collectionType
     * \return
     */
    Contants::CollectionType collectionType() const;
    void setCollectionType(Contants::CollectionType collectionType);

signals:
    void nameChanged();
    void typeChanged();
    void valueChanged();
    void collectionTypeChanged();

private:
    XOOO_DECLARE_PRIVATE(ContextVariable)
};
}
}
