#include "sequenceflow.h"
#include "expression.h"
#include "bpmn_constants.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class SequenceFlowPrivate
{
public:
    XmlDom::XmlReferenceAttribute* sourceRef = nullptr;
    XmlDom::XmlReferenceAttribute* targetRef = nullptr;
    XmlDom::XmlAttribute* conditionExpression = nullptr;
};
}

SequenceFlow::SequenceFlow(XmlDom::XmlTag *tag)
    : FlowElement(tag), d_ptr(new SequenceFlowPrivate)
{
    d_ptr->sourceRef = attributeBuilder()->createReferenceAttribute("id", "sourceRef", this, &SequenceFlow::sourceRefChanged);
    d_ptr->targetRef = attributeBuilder()->createReferenceAttribute("id", "targetRef", this, &SequenceFlow::targetRefChanged);
    d_ptr->conditionExpression = attributeBuilder()->createAttribute("conditionExpression", this, &SequenceFlow::conditionExpressionChanged);
}

SequenceFlow::~SequenceFlow()
{

}

BaseElement *SequenceFlow::sourceRef()
{
    return d_ptr->sourceRef->referenceElement<BaseElement*>();
}

void SequenceFlow::setSourceRef(BaseElement *value)
{
    d_ptr->sourceRef->setReferenceElement(value);
}

BaseElement *SequenceFlow::targetRef()
{
    return d_ptr->targetRef->referenceElement<BaseElement*>();
}

void SequenceFlow::setTargetRef(BaseElement *value)
{
    d_ptr->targetRef->setReferenceElement(value);
}

Expression *SequenceFlow::conditionExpression()
{
    return d_ptr->conditionExpression->value<Expression*>();
}

void SequenceFlow::setConditionExpression(Expression *value)
{
    d_ptr->conditionExpression->setValue(value);
}

}

