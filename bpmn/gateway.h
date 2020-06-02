/*****************************************************************************
* gateway.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/flownode.h>
#include <QObject>
#include <bpmn/bpmn_global.h>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Gateway)
/*!
 * \brief The Gateway class is an abstract type. Its concrete subclasses define the specific semantics of individual Gateway
 * types, defining how the Gateway behaves in different situations
 */
class BPMN_LIBRARY_EXPORT Gateway : public FlowNode
{
    Q_OBJECT
    Q_ENUMS(GatewayDirection)
    Q_PROPERTY(GatewayDirection gatewayDirection READ gatewayDirection WRITE setGatewayDirection NOTIFY gatewayDirectionChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Gateway>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_GATEWAY);
    }

    enum GatewayDirection {
        //The Gateway MAY have any number of incoming and outgoing Sequence Flows.
        Unspecified = 0,

        // This Gateway MAY have multiple incoming
        // Sequence Flows but MUST have no more than one (1)
        // outgoing Sequence Flow.
        Converging,

        // This Gateway MAY have multiple outgoing
        // Sequence Flows but MUST have no more than one (1)
        // incoming Sequence Flow
        Diverging,

        // This Gateway contains multiple outgoing and
        // multiple incoming Sequence Flows.
        Mixed
    };


    Q_INVOKABLE Gateway(XmlDom::XmlTag *tag);
    ~Gateway();

    GatewayDirection gatewayDirection();
    void setGatewayDirection(GatewayDirection value);

    Gateway *openingGateway() const;
    void setOpeningGateway(Gateway *gateway);

    Gateway *closingGateway() const;
    void setClosingGateway(Gateway *gateway);

signals:
    void gatewayDirectionChanged();
    void openingGatewayChanged();
    void closingGatewayChanged();

private:
    DECLARE_PRIVATE(Gateway)
};
}
Q_DECLARE_METATYPE(Bpmn::Gateway*)
Q_DECLARE_METATYPE(Bpmn::Gateway::GatewayDirection)
