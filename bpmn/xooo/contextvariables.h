/*****************************************************************************
 * contextvariables.h
 *
 * Created: 11.04.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/extension.h>
#include <bpmn/xooo/contextvariable.h>
#include <QObject>
namespace Bpmn {
namespace Xooo {
XOOO_FORWARD_DECLARE_PRIVATE(ContextVariables)
class BPMN_LIBRARY_EXPORT ContextVariables : public Extension
{
    Q_OBJECT
    Q_PRIVATE_PROPERTY(d_ptr, QQmlListProperty<ContextVariable> variables READ getVariables NOTIFY variablesChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<ContextVariables>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_CONTEXT_VARIABLES);
    }
    Q_INVOKABLE ContextVariables(XmlDom::XmlTag *tag);
    ~ContextVariables();

    QList<ContextVariable *> variables() const;
    ContextVariable *findVariable(const QString &name);
signals:
    void variablesChanged();
private:
    XOOO_DECLARE_PRIVATE(ContextVariables)
};
}
}
