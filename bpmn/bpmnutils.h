/*****************************************************************************
 * bpmnutils.h
 *
 * Created: 11.10.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <bpmn/bpmn_global.h>
#include <xmldom/xmlmodeldocument.h>
#include <QObject>
namespace Bpmn {
class Process;
class BaseElement;
class Artifact;
class Association;
class FlowNode;
class StartEvent;
class EndEvent;
class SequenceFlow;
/*!
 * \brief The BpmnUtils class helps to work with Process Document
 */
class BPMN_LIBRARY_EXPORT BpmnUtils
{
public:
    /*!
     * \brief Returns first process for given document
     */
    static Bpmn::Process *findProcess(XmlDom::XmlModelDocument *document);
    /*!
     * \brief Returns start event of the document
     */
    static Bpmn::StartEvent *findStartEvent(XmlDom::XmlModelDocument *document);
    /*!
     * \brief Returns end event of the document
     */
    static Bpmn::EndEvent *findEndEvent(XmlDom::XmlModelDocument *document);
    /*!
     * \brief Returns element with given id
     */
    static Bpmn::BaseElement *findElementWithId(XmlDom::XmlModelDocument *document, const QString &id);
    // Edge utils:
    static Bpmn::SequenceFlow *createEdge(Bpmn::BaseElement *parent);

    //NOT TESTED
    static Bpmn::SequenceFlow *connectElements(Bpmn::FlowNode *source, Bpmn::FlowNode *target);

    static void retargetEdge(Bpmn::SequenceFlow *edge, Bpmn::FlowNode *newTarget);
    static void changeEdgeSource(Bpmn::SequenceFlow *edge, Bpmn::FlowNode *newSource);
    static void reconnectEdge(Bpmn::SequenceFlow *newEdge, Bpmn::FlowNode *source, Bpmn::FlowNode *target);

    // Node utils
    /*!
     * \brief Inserts new element connecting target edge with new element, and creating
     * new seuqence flow to the old targetEdge target. Gateways will be inserted always in couple
     */
    static void insertNodeOnEdge(Bpmn::FlowNode *newNode, Bpmn::SequenceFlow *targetEdge);
    /*!
     * \brief Removes node from flow chain, connecting incomming edge to outgoing element
     * cannot remove start end events, it will cause chain damage. Gateways will be removed in couple
     */
    static void removeNodeFromFlowChain(Bpmn::FlowNode *node);
    /*!
     * \brief Extracts node from flow chain leaving the element free inside of process tag
     */
    static void extractNodeFromFlowChain(Bpmn::FlowNode *node);
    /*!
     * \brief Replaces element in flow chain, reconects all edges to new element,
     * and removes old one
     */
    static void replaceNodeInFlow(FlowNode *newNode, FlowNode *targeNode);

    // Artifacts
    /*!
     * \brief Removes artifact with all associations
     */
    static void removeArtifact(Bpmn::Artifact *artifact);
    /*!
     * \brief Finds all associations with target=targetElement, and remove
     * them
     */
    static void removeArtifactsForElement(Bpmn::BaseElement *targetElement);

    // Type checking
    static bool isStartEvent(const Bpmn::BaseElement *element);
    static bool isConnection(const Bpmn::BaseElement *element);
    static bool isGateway(const Bpmn::BaseElement *element);
    static bool isActivity(const Bpmn::BaseElement *element);
    static bool isTextAnnotation(const Bpmn::BaseElement *element);
    static bool isDataObject(const Bpmn::BaseElement *element);

};
}
