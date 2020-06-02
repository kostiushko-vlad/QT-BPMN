#include "excusivegateway.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ExcusiveGatewayPrivate
{
public:

};
}

ExcusiveGateway::ExcusiveGateway(XmlDom::XmlTag *tag)
: FlowNode(tag), d_ptr(new ExcusiveGatewayPrivate)
{

}

ExcusiveGateway::~ExcusiveGateway()
{

}

}

