/*****************************************************************************
* flownode.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/flowelement.h>
#include <QObject>
#include <QQmlListProperty>

namespace Bpmn {
class SequenceFlow;
FORWARD_DECLARE_PRIVATE(FlowNode)
/*!
 * \brief The FlowNode element is used to provide a single element as the source and target Sequence Flow associations
 * instead of the individual associations of the elements that can connect to Sequence Flows (see above).
 * Only the Gateway, Activity, Choreography Activity, and Event elements can connect to Sequence Flows and
 * thus, these elements are the only ones that are sub-classes of FlowNode.
 */
class BPMN_LIBRARY_EXPORT FlowNode : public FlowElement
{
    Q_OBJECT

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<FlowNode>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_FLOW_NODE);
    }

     Q_INVOKABLE FlowNode(XmlDom::XmlTag *tag);
    ~FlowNode();

    /*!
     * \brief This attribute identifies the incoming Sequence Flow of the FlowNode
     * \return
     */
    QList<Bpmn::SequenceFlow *> incoming();

    /*!
     * \brief This attribute identifies the outgoing Sequence Flow of the FlowNode.
     * This is an ordered collection.
     */
    QList<Bpmn::SequenceFlow *> outgoing();

public slots:
    void addIncoming(Bpmn::SequenceFlow* flow);
    void addOutgoing(Bpmn::SequenceFlow* flow);
    void removeIncoming(Bpmn::SequenceFlow* flow);
    void removeOutgoing(Bpmn::SequenceFlow* flow);

signals:
    void incomingChanged();
    void outgoingChanged();

private:
    DECLARE_PRIVATE(FlowNode)
};
}
Q_DECLARE_METATYPE(Bpmn::FlowNode*)
