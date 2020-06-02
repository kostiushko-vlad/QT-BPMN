/*****************************************************************************
 * expressionflow.h
 *
 * Created: 26.04.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <bpmn/sequenceflow.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(ExpressionFlow)
class BPMN_LIBRARY_EXPORT ExpressionFlow : public SequenceFlow
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<ExpressionFlow>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_EXPRESSION_FLOW);
    }
    Q_INVOKABLE ExpressionFlow(XmlDom::XmlTag *tag);
    ~ExpressionFlow();

public slots:

signals:

private:
    DECLARE_PRIVATE(ExpressionFlow)
};
}
Q_DECLARE_METATYPE(Bpmn::ExpressionFlow*)
