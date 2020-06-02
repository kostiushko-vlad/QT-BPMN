/*****************************************************************************
* sequenceflow.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/flowelement.h>
#include <QObject>
namespace Bpmn {
class Expression;
FORWARD_DECLARE_PRIVATE(SequenceFlow)
/*!
 * \brief The SequenceFlow class
 */

class BPMN_LIBRARY_EXPORT SequenceFlow : public FlowElement
{
    Q_OBJECT
    Q_PROPERTY(Bpmn::BaseElement* sourceRef READ sourceRef WRITE setSourceRef NOTIFY sourceRefChanged)
    Q_PROPERTY(Bpmn::BaseElement* targetRef READ targetRef WRITE setTargetRef NOTIFY targetRefChanged)
    Q_PROPERTY(Bpmn::Expression* conditionExpression READ conditionExpression WRITE setConditionExpression NOTIFY conditionExpressionChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<SequenceFlow>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_SEQUENCE_FLOW);
    }
    Q_INVOKABLE SequenceFlow(XmlDom::XmlTag *tag);
    ~SequenceFlow();

    /*!
     * \brief The FlowNode that the Sequence Flow is connecting from.
     */
    BaseElement *sourceRef();
    void setSourceRef(BaseElement* element);

    /*!
     * \brief The FlowNode that the Sequence Flow is connecting to
     */
    BaseElement *targetRef();
    void setTargetRef(BaseElement* element);

    /*!
     * \brief An optional boolean Expression that acts as a gating condition
     */
    Bpmn::Expression *conditionExpression();
    void setConditionExpression(Bpmn::Expression* value);

signals:
    void sourceRefChanged();
    void targetRefChanged();
    void conditionExpressionChanged();

private:
    DECLARE_PRIVATE(SequenceFlow)
};
}
Q_DECLARE_METATYPE(Bpmn::SequenceFlow*)
