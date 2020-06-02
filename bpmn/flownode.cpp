#include "flownode.h"
#include "incoming.h"
#include "outgoing.h"
#include "sequenceflow.h"
#include "bpmn_constants.h"
#include "xmldom/xmlattributes.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class FlowNodePrivate
{
public:
    FlowNodePrivate(FlowNode *object): q(object){}

    XmlDom::XmlReferenceListAttribute* incoming = nullptr;
    XmlDom::XmlReferenceListAttribute* outgoing = nullptr;

private:
    FlowNode *q = nullptr;
};
}

FlowNode::FlowNode(XmlDom::XmlTag *tag)
    : FlowElement(tag), d_ptr(new FlowNodePrivate(this))
{
    d_ptr->incoming = attributeBuilder()->createReferenceListAttribute<Incoming>("id", this, &FlowNode::incomingChanged);
    d_ptr->outgoing = attributeBuilder()->createReferenceListAttribute<Outgoing>("id", this, &FlowNode::outgoingChanged);
}

FlowNode::~FlowNode()
{

}

QList<SequenceFlow *> FlowNode::incoming()
{
    return toList<SequenceFlow*>(d_ptr->incoming->references());
}

QList<SequenceFlow *> FlowNode::outgoing()
{
    return toList<SequenceFlow*>(d_ptr->outgoing->references() );
}

void FlowNode::addIncoming(SequenceFlow *flow)
{
    d_ptr->incoming->append(flow);
    emit incomingChanged();
}

void FlowNode::addOutgoing(SequenceFlow *flow)
{
    d_ptr->outgoing->append(flow);
    emit outgoingChanged();
}

void FlowNode::removeIncoming(SequenceFlow *flow)
{
    d_ptr->incoming->remove(flow);
}

void FlowNode::removeOutgoing(SequenceFlow *flow)
{
    d_ptr->outgoing->remove(flow);
}

}
#include "moc_flownode.cpp"
