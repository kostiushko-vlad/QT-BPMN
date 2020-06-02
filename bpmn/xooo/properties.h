/*****************************************************************************
 * properties.h
 *
 * Created: 05.04.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/extension.h>
#include <QQmlListProperty>
#include <QObject>
namespace Bpmn {
namespace Xooo {
class Property;
XOOO_FORWARD_DECLARE_PRIVATE(Properties)
class BPMN_LIBRARY_EXPORT Properties : public Extension
{
    Q_OBJECT
    Q_PRIVATE_PROPERTY(d_ptr, QQmlListProperty<Property> properties READ getProperties NOTIFY propertiesChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Properties>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_PROPERTIES);
    }
    Q_INVOKABLE Properties(XmlDom::XmlTag *tag);
    ~Properties();

    /*!
     * \brief List of properties
     * \return`
     */
    QList<Property *> properties() const;
    Property *findProperty(const QString &name);
    void removeProperty(const QString &name);
    Property *insertProperty(const QString &name, const QString &value);

signals:
    void propertiesChanged();
    void propertyChanged(const QString &name);

private:
    XOOO_DECLARE_PRIVATE(Properties)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Xooo::Properties*)
