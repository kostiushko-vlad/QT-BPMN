#include "gateway.h"
#include "bpmn_constants.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class GatewayPrivate
{
public:
    XmlDom::XmlAttribute* gatewayDirection = nullptr;
    XmlDom::XmlReferenceAttribute *openingGateway = nullptr;
    XmlDom::XmlReferenceAttribute *closingGateway = nullptr;
};
}

Gateway::Gateway(XmlDom::XmlTag *tag)
: FlowNode(tag), d_ptr(new GatewayPrivate)
{
    d_ptr->gatewayDirection = attributeBuilder()->createAttribute("gatewayDirection", this, &Gateway::gatewayDirectionChanged);
    d_ptr->gatewayDirection->setEnumerator("GatewayDirection");
    d_ptr->gatewayDirection->setValue(GatewayDirection::Unspecified);
    d_ptr->openingGateway = attributeBuilder()->createReferenceAttribute("id", Contants::BPMN20_NS, "openingGateway", this, &Gateway::openingGatewayChanged);
    d_ptr->closingGateway = attributeBuilder()->createReferenceAttribute("id", Contants::BPMN20_NS, "closingGateway", this, &Gateway::openingGatewayChanged);
}

Gateway::~Gateway()
{

}

Gateway::GatewayDirection Gateway::gatewayDirection()
{
    return d_ptr->gatewayDirection->value<Gateway::GatewayDirection>();
}

void Gateway::setGatewayDirection(Gateway::GatewayDirection value)
{
    d_ptr->gatewayDirection->setValue(value);
}

void Gateway::setOpeningGateway(Gateway *gateway)
{
    d_ptr->openingGateway->setReferenceElement(gateway);
}

void Gateway::setClosingGateway(Gateway *gateway)
{
    d_ptr->closingGateway->setReferenceElement(gateway);
}

Gateway *Gateway::openingGateway() const
{
    return d_ptr->openingGateway->referenceElement<Gateway*>();
}

Gateway *Gateway::closingGateway() const
{
    return d_ptr->closingGateway->referenceElement<Gateway*>();
}

}

