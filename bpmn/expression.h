/*****************************************************************************
* expression.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Expression)
/*!
 * \brief The Expression class is used to specify an Expression using natural-language text. These Expressions are not
 * executable and are considered underspecified
 */
class BPMN_LIBRARY_EXPORT Expression : public BaseElement
{
    Q_OBJECT
public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Expression>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_EXPRESSION);
    }

    Q_INVOKABLE Expression(XmlDom::XmlTag *tag);
    ~Expression();

private:
    DECLARE_PRIVATE(Expression)
};
}
Q_DECLARE_METATYPE(Bpmn::Expression*)
