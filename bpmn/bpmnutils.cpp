#include "bpmnutils.h"
#include "bpmn/bpmntypes.h"
#include "extensionelements.h"
#include "bpmn_constants.h"
namespace Bpmn {
inline Definitions* getDefinitions(XmlDom::XmlModelDocument *doc)
{
    GUARD(!doc, return nullptr)

    return qobject_cast<Definitions*>(doc->rootElement());
}
inline Process* getProcess(XmlDom::XmlModelDocument *doc)
{
    GUARD(!doc, return nullptr)

    // Get root definitions element
    auto definitions = getDefinitions(doc);
    GUARD(!definitions, return nullptr)

    // Find process
    auto process = definitions->child<Process>();
    return process;
}

inline bool isSingleElementInGatewayPath(Bpmn::FlowNode *node) {
    bool result = false;
    Bpmn::SequenceFlow *incomingEdge = node->incoming()[0];
    Bpmn::SequenceFlow *outgoingEdge = node->outgoing()[0];

    // Check if incoming element is  gateway
    if(auto openingGateway = qobject_cast<Bpmn::Gateway*>(incomingEdge->sourceRef())){
        // Check if incoming element is opening gateway
        if(auto closingGateway = openingGateway->closingGateway()) {
            // Check if outgoing element is closing gateway
            if(closingGateway == outgoingEdge->targetRef()) {
                result = true;
            }
        }
    }
    return result;
}


inline void clearSequencePath(Bpmn::Process *process, Bpmn::SequenceFlow *startFlow,
                              Bpmn::FlowNode *stopNode) {
    process->removeChild(startFlow);
    if(startFlow->targetRef() == stopNode) {
        return;
    }
    auto target = qobject_cast<Bpmn::FlowNode*>(startFlow->targetRef());
    for(Bpmn::BaseElement *outgoing: target->outgoing()) {
        auto flow = qobject_cast<Bpmn::SequenceFlow*>(outgoing);
        clearSequencePath(process, flow, stopNode);
    }
    Bpmn::BpmnUtils::removeArtifactsForElement(target);
    process->removeChild(target);
}

inline void removeGatewayFromProcess(Bpmn::Process *process, Bpmn::Gateway* gateway) {
    for(Bpmn::BaseElement *outgoing: gateway->outgoing()) {
        auto flow = qobject_cast<Bpmn::SequenceFlow*>(outgoing);
        clearSequencePath(process, flow, gateway->closingGateway());
    }
    Bpmn::BpmnUtils::removeArtifactsForElement(gateway->closingGateway());
    process->removeChild(gateway->closingGateway());
}
// Returns opening gateway, otherwise nullptr
inline Bpmn::Gateway* getOpeningGateway(Bpmn::FlowNode *node) {
    if(auto gateway = qobject_cast<Bpmn::Gateway*>(node)){
        if(gateway->closingGateway()) {
            return gateway;
        }
    }
    return nullptr;
}

inline void removeUnusedGatewayPaths(Bpmn::Process *process, Bpmn::Gateway* gateway) {
    if(gateway->outgoing().count()> 1) {
        for(Bpmn::SequenceFlow *outgoing: gateway->outgoing()) {
            if(outgoing->targetRef() == gateway->closingGateway()) {
                gateway->removeOutgoing(outgoing);
                gateway->closingGateway()->removeIncoming(outgoing);
                process->removeChild(outgoing);
            }
        }
    }
}
Process *BpmnUtils::findProcess(XmlDom::XmlModelDocument *document)
{
    GUARD(!document, return nullptr)

    return document->rootElement()->child<Process>(true);
}

StartEvent *BpmnUtils::findStartEvent(XmlDom::XmlModelDocument *document)
{
    // Find process inside document
    Process* process = getProcess(document);
    GUARD(!process, return nullptr)

    // Find start event for input parameters
    auto startEvent = process->child<Bpmn::StartEvent>();
    GUARD(!startEvent, return nullptr)

    return startEvent;
}

EndEvent *BpmnUtils::findEndEvent(XmlDom::XmlModelDocument *document)
{
    // Find process inside document
    Process* process = getProcess(document);
    GUARD(!process, return nullptr)

    // Find end event as child of the process
    auto endEvent = process->child<Bpmn::EndEvent>();
    GUARD(!endEvent, return nullptr)

    return endEvent;
}

BaseElement *BpmnUtils::findElementWithId(XmlDom::XmlModelDocument *document, const QString &id)
{
    BaseElement *foundElement = nullptr;
    reverseForeach(document->modelElements(), [=, &foundElement](XmlDom::XmlModelElement *element) {
        if(auto bpmnElement = qobject_cast<Bpmn::BaseElement*>(element)) {
            if(bpmnElement->id() == id){
                foundElement = bpmnElement;
            }
        }
    });
    return foundElement;
}

Bpmn::SequenceFlow *BpmnUtils::createEdge(Bpmn::BaseElement *parent)
{
    Bpmn::BpmnFactory *bpmnFactory = Bpmn::BpmnFactory::instance();
    return bpmnFactory->createInstanceOfModel<Bpmn::SequenceFlow>(parent->document(), parent);
}

SequenceFlow *BpmnUtils::connectElements(FlowNode *source, FlowNode *target)
{
    GUARD(!source || !target, return nullptr)

    Bpmn::Process *process = findProcess(source->document());
    if(process) {
        Bpmn::SequenceFlow *edgeBetweenGateways = createEdge(process);
        reconnectEdge(edgeBetweenGateways, source, target);
    }
    return nullptr;
}

void BpmnUtils::retargetEdge(SequenceFlow *edge, FlowNode *newTarget)
{
    // Remove incoming link from target
    Bpmn::BaseElement *oldTarget = edge->targetRef();

    auto oldTargetNode = qobject_cast<Bpmn::FlowNode *>(oldTarget);
    if(oldTargetNode) {
        // Remove link from old edge
        oldTargetNode->removeIncoming(edge);
    }
    // Set new target
    edge->setTargetRef(newTarget);
    // Add incoming link to the new target
    newTarget->addIncoming(edge);
}

void BpmnUtils::changeEdgeSource(SequenceFlow *edge, FlowNode *newSource)
{
    // Remove incoming ling from target
    Bpmn::BaseElement *oldSource = edge->sourceRef();

    auto oldSourceNode = qobject_cast<Bpmn::FlowNode *>(oldSource);
    if(oldSourceNode) {
        // Remove link from old edge
        oldSourceNode->removeOutgoing(edge);
    }
    // Set new target
    edge->setSourceRef(newSource);
    // Add incoming link to the new target
    newSource->addOutgoing(edge);
}
void BpmnUtils::reconnectEdge(SequenceFlow *newEdge, FlowNode *source, FlowNode *target)
{
    changeEdgeSource(newEdge, source);
    retargetEdge(newEdge, target);
}

void BpmnUtils::insertNodeOnEdge(FlowNode *newNode, SequenceFlow *targetEdge)
{
    GUARD(!newNode || !targetEdge, return)

    Bpmn::Process *process = findProcess(newNode->document());
    auto edgeOldTarget = qobject_cast<Bpmn::FlowNode *>(targetEdge->targetRef());
    retargetEdge(targetEdge, newNode);

    // We insert gateways always in coupl
    if(auto firstGateway = qobject_cast<Bpmn::Gateway*>(newNode)) {
        // Create second gateway node
        auto secondGateway = firstGateway->closingGateway() ? firstGateway->closingGateway()
                                                            : newNode->type()->newModelElementInstance<Bpmn::Gateway>(newNode->document());
        process->appendChild(secondGateway);

        // Create edge between them
        Bpmn::SequenceFlow *edgeBetweenGateways = createEdge(process);

        // Link two gateways for autolayouter algorithm
        firstGateway->setClosingGateway(secondGateway);
        secondGateway->setOpeningGateway(firstGateway);

        // Connect edge between gateways
        reconnectEdge(edgeBetweenGateways, firstGateway, secondGateway);
        newNode = secondGateway;
    }

    // Create edge to old target
    Bpmn::SequenceFlow *edgeToOldTarget = createEdge(process);
    reconnectEdge(edgeToOldTarget, newNode, edgeOldTarget);
}
void BpmnUtils::removeNodeFromFlowChain(FlowNode *node)
{
    GUARD(!node || node->type()->isTypeOf<Bpmn::StartEvent>()
               || node->type()->isTypeOf<Bpmn::EndEvent>(), return)

    QList<Bpmn::SequenceFlow*> outgoingEdges = node->outgoing();
    QList<Bpmn::SequenceFlow*> incomingEdges = node->incoming();
    if(!outgoingEdges.isEmpty() && !incomingEdges.isEmpty()){
        Bpmn::Process *process = findProcess(node->document());
        Bpmn::SequenceFlow *incomingEdge = incomingEdges[0];
        Bpmn::SequenceFlow *outgoingEdge = outgoingEdges[0];
        auto outgoingTarget = qobject_cast<Bpmn::FlowNode*>(outgoingEdge->targetRef());
        auto incomingTarget = qobject_cast<Bpmn::FlowNode*>(incomingEdge->sourceRef());

        // Check if removing single element in gateway path
        // but only if there are others paths
        if(isSingleElementInGatewayPath(node) && incomingTarget->outgoing().count() > 1) {
            incomingTarget->removeOutgoing(incomingEdge);
            outgoingTarget->removeIncoming(outgoingEdge);
            process->removeChild(incomingEdge);
        } else if(Bpmn::Gateway* gateway = getOpeningGateway(node)) {
            removeGatewayFromProcess(process, gateway);
            auto outgoingEdge = qobject_cast<Bpmn::SequenceFlow *>(gateway->closingGateway()->outgoing()[0]);
            auto newTarget = qobject_cast<Bpmn::FlowNode *>(outgoingEdge->targetRef());
            newTarget->removeIncoming(outgoingEdge);
            retargetEdge(incomingEdge, newTarget);
            if(auto parentGateway = qobject_cast<Bpmn::Gateway*>(incomingEdge->sourceRef())) {
                removeUnusedGatewayPaths(process, parentGateway);
            }
            process->removeChild(outgoingEdge);
        } else {
            outgoingTarget->removeIncoming(outgoingEdge);
            retargetEdge(incomingEdge, outgoingTarget);
        }
        node->removeOutgoing(outgoingEdge);
        removeArtifactsForElement(node);
        process->removeChild(outgoingEdge);
        process->removeChild(node);
    }
}

void BpmnUtils::extractNodeFromFlowChain(FlowNode *node)
{
    Bpmn::SequenceFlow *incommingFlow = node->incoming().first();
    Bpmn::SequenceFlow *outgoingFlow = node->outgoing().first();
    GUARD(!incommingFlow || !outgoingFlow, return)

    auto outgoingNode = qobject_cast<FlowNode*>(outgoingFlow->targetRef());
    retargetEdge(incommingFlow, outgoingNode);

    node->removeOutgoing(outgoingFlow);
    outgoingNode->removeIncoming(outgoingFlow);

    Bpmn::Process *process = findProcess(node->document());
    process->removeChild(outgoingFlow);
}

void BpmnUtils::replaceNodeInFlow(FlowNode *newNode, FlowNode *targetNode)
{
    Bpmn::Process* process = getProcess(newNode->document());
    QList<Bpmn::SequenceFlow*> incoming = targetNode->incoming();
    QList<Bpmn::SequenceFlow*> outgoing = targetNode->outgoing();

    // Change incoming
    for(Bpmn::SequenceFlow* edge : incoming) {
        retargetEdge(edge, newNode);
    }

    // Add gateways always in pair
    if(auto gateway = qobject_cast<Bpmn::Gateway*>(newNode)) {
        // Create second gatewat
        Bpmn::Gateway *secondGateway = newNode->type()->newModelElementInstance<Bpmn::Gateway>(newNode->document());

        // Create edge between gateways
        Bpmn::SequenceFlow *flowForGateway = createEdge(process);
        changeEdgeSource(flowForGateway, gateway);
        retargetEdge(flowForGateway, secondGateway);

        // Link gateways
        gateway->setClosingGateway(secondGateway);
        secondGateway->setOpeningGateway(gateway);

        // Set new node as second gateway
        newNode = secondGateway;
    }

    // Change outgoing
    for(Bpmn::SequenceFlow *edge : outgoing) {
        changeEdgeSource(edge, newNode);
    }

    // Remove old node
    removeArtifactsForElement(targetNode);
    process->removeChild(targetNode);
}


void BpmnUtils::removeArtifact(Artifact *artifact)
{
    GUARD(!artifact, return)
    Bpmn::Process *process = findProcess(artifact->document());
    QList<Bpmn::Association*> associations = artifact->document()->rootElement()->children<Bpmn::Association>(true);
    for(Bpmn::Association *association: associations) {
        if(association->sourceRef() == artifact) {
            process->removeChild(association);
        }
    }
    process->removeChild(artifact);
}

void BpmnUtils::removeArtifactsForElement(BaseElement *targetElement)
{
    QList<Bpmn::Association*> associations = targetElement->document()->rootElement()->children<Bpmn::Association>(true);
    for(Bpmn::Association *association: associations) {
        if(association->targetRef() == targetElement) {
            removeArtifact(qobject_cast<Bpmn::Artifact*>(association->sourceRef()));
        }
    }
}

bool BpmnUtils::isStartEvent(const Bpmn::BaseElement *element)
{
    GUARD(!element || !element->type(), return false)
    return element->type()->isTypeOf<Bpmn::StartEvent>();
}
bool BpmnUtils::isConnection(const Bpmn::BaseElement *element)
{
    GUARD(!element || !element->type(), return false)
    XmlDom::XmlModelElementType *type = element->type();
    return type->isTypeOf<Bpmn::SequenceFlow>()
        || type->isTypeOf<Bpmn::Association>();
}

bool BpmnUtils::isTextAnnotation(const Bpmn::BaseElement *element)
{
    GUARD(!element || !element->type(), return false)
    XmlDom::XmlModelElementType *type = element->type();
    return type->isTypeOf<Bpmn::TextAnnotation>();
}

bool BpmnUtils::isDataObject(const Bpmn::BaseElement *)
{
    // Not implemented yet
    Q_UNREACHABLE_IMPL();
}

bool BpmnUtils::isGateway(const Bpmn::BaseElement *element)
{
    GUARD(!element || !element->type(), return false)
    XmlDom::XmlModelElementType *type = element->type();
    return type->isTypeOf<Bpmn::Gateway>()
        || type->isTypeOf<Bpmn::ExcusiveGateway>();
}

bool BpmnUtils::isActivity(const Bpmn::BaseElement *element)
{
    GUARD(!element || !element->type(), return false)
    XmlDom::XmlModelElementType *type = element->type();
    return type->isTypeOf<Bpmn::Activity>();
}

}
