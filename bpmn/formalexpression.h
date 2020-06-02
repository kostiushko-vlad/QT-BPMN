/*****************************************************************************
* formalexpression.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/expression.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(FormalExpression)
/*!
 * \brief The FormalExpression class is used to specify an executable Expression using a specified Expression
 * language. A natural-language description of the Expression can also be specified, in addition to the formal
 * specification.
 */
class BPMN_LIBRARY_EXPORT FormalExpression : public Expression
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<FormalExpression>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_FORMAL_EXPRESSION);
    }

    Q_INVOKABLE FormalExpression(XmlDom::XmlTag *tag);
    ~FormalExpression();

    /*!
     * \brief Overrides the Expression language specified in the Definitions
     */
    QString language() const;
    void setLanguage(const QString &value);

    /*!
     * \briefThe body of the Expression.
     * Note that this attribute is not relevant when the XML Schema is used for
     * interchange. Instead, the FormalExpression complex type supports mixed
     * content. The body of the Expression would be specified as element content.
     * For example:
     * <formalExpression id=“ID_2">
     *  count(../dataObject[id="CustomerRecord_1"]/emailAddress) > 0
     * </formalExpression>
     */
    QString body() const;
    void setBody(const QString &value);

signals:
    void languageChanged();
    void bodyChanged();

private:
    DECLARE_PRIVATE(FormalExpression)
};
}
Q_DECLARE_METATYPE(Bpmn::FormalExpression*)
