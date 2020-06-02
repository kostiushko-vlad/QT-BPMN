#include "formalexpression.h"
#include "bpmn_constants.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class FormalExpressionPrivate
{
public:
    XmlDom::XmlAttribute* language;
    XmlDom::XmlAttribute* body;

};
}

FormalExpression::FormalExpression(XmlDom::XmlTag *tag)
: Expression(tag), d_ptr(new FormalExpressionPrivate)
{
    d_ptr->language = attributeBuilder()->createAttribute("language", this, &FormalExpression::languageChanged);
    d_ptr->body = attributeBuilder()->createAttribute("body", this, &FormalExpression::bodyChanged);
}

FormalExpression::~FormalExpression()
{

}

QString FormalExpression::language() const
{
    return d_ptr->language->toString();
}

void FormalExpression::setLanguage(const QString &value)
{
    d_ptr->language->setValue(value);
}

QString FormalExpression::body() const
{
    return d_ptr->body->toString();
}

void FormalExpression::setBody(const QString &value)
{
    d_ptr->body->setValue(value);
}

}

