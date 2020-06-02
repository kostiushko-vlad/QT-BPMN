/*****************************************************************************
 * parameters.h
 *
 * Created: 10.04.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/extension.h>
#include <bpmn/xooo/parameter.h>
#include <QQmlListProperty>
namespace Bpmn {
namespace Xooo {
XOOO_FORWARD_DECLARE_PRIVATE(Parameters)
class BPMN_LIBRARY_EXPORT Parameters : public Extension
{
    Q_OBJECT
    Q_PRIVATE_PROPERTY(d_ptr, QQmlListProperty<Parameter> parameters READ getParameters NOTIFY parametersChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Parameters>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_PARAMETERS);
    }
    Q_INVOKABLE Parameters(XmlDom::XmlTag *tag);
    ~Parameters();

    /*!
     * \brief List of properties
     * \return`
     */
    QList<Parameter *> parameters() const;
    Parameter *findParameter(const QString &name);

signals:
    void parametersChanged();

private:
    XOOO_DECLARE_PRIVATE(Parameters)
};
}
}
