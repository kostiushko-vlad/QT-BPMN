/*****************************************************************************
 * property.h
 *
 * Created: 05.04.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
namespace Xooo {
XOOO_FORWARD_DECLARE_PRIVATE(Property)
class BPMN_LIBRARY_EXPORT Property : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Property>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_PROPERTY);
    }
    Q_INVOKABLE Property(XmlDom::XmlTag *tag);
    ~Property();

    /*!
     * \brief name
     * \return
     */
    QString name() const;
    void setName(const QString &value);

    /*!
     * \brief value
     * \return
     */
    QString value() const;
    void setValue(const QString &value);

signals:
    void nameChanged();
    void dispalyNameChanged();
    void typeChanged();
    void valueChanged();

private:
    XOOO_DECLARE_PRIVATE(Property)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Xooo::Property*)
