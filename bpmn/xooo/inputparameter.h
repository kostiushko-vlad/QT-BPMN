/*****************************************************************************
 * inputparameter.h
 *
 * Created: 11.04.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/xooo/parameter.h>
#include <QObject>
namespace Bpmn {
namespace Xooo {
XOOO_FORWARD_DECLARE_PRIVATE(InputParameter)
class BPMN_LIBRARY_EXPORT InputParameter : public Parameter
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<InputParameter>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_INPUT_PARAMETER);
    }
    Q_INVOKABLE InputParameter(XmlDom::XmlTag *tag);
    ~InputParameter();

public slots:

signals:

private:
    XOOO_DECLARE_PRIVATE(InputParameter)
};
}
}
