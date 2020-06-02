/*****************************************************************************
 * outputparameter.h
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
XOOO_FORWARD_DECLARE_PRIVATE(OutputParameter)
class BPMN_LIBRARY_EXPORT OutputParameter : public Parameter
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<OutputParameter>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_OUTPUT_PARAMETER);
    }
    Q_INVOKABLE OutputParameter(XmlDom::XmlTag *tag);
    ~OutputParameter();

private:
    XOOO_DECLARE_PRIVATE(OutputParameter)
};
}
}
