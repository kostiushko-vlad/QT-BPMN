#include "expressionflow.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ExpressionFlowPrivate
{
public:

};
}

ExpressionFlow::ExpressionFlow(XmlDom::XmlTag *tag)
        : SequenceFlow(tag), d_ptr(new ExpressionFlowPrivate)
{

}

ExpressionFlow::~ExpressionFlow()
{

}

}

