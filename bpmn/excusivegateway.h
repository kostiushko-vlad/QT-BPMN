/*****************************************************************************
* excusivegateway.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/flownode.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(ExcusiveGateway)
/*!
 * \brief The Exclusive Gateway element inherits the attributes and model associations of Gateway
 */
class BPMN_LIBRARY_EXPORT ExcusiveGateway : public FlowNode
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<ExcusiveGateway>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_EXCLUSIVE_GATEWAY);
    }

    Q_INVOKABLE ExcusiveGateway(XmlDom::XmlTag *tag);
    ~ExcusiveGateway();

private:
    DECLARE_PRIVATE(ExcusiveGateway)
};
}
Q_DECLARE_METATYPE(Bpmn::ExcusiveGateway*)
