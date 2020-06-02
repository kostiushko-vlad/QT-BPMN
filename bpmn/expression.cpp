#include "expression.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ExpressionPrivate
{
public:

};
}

Expression::Expression(XmlDom::XmlTag *tag)
: BaseElement(tag), d_ptr(new ExpressionPrivate)
{

}

Expression::~Expression()
{

}

}

