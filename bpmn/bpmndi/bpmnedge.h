/*****************************************************************************
* bpmnedge.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/labelededge.h>
#include <QObject>
namespace Bpmn {
namespace BpmnDi {
class BpmnLabel;
FORWARD_DECLARE_PRIVATE(BpmnEdge)
/*!
 * \brief BpmnEdge is a kind of edge that can depict a relationship between two BPMN model elements
 */
class BPMN_LIBRARY_EXPORT BpmnEdge : public Di::LabeledEdge
{
    Q_OBJECT
    Q_PROPERTY(Bpmn::BpmnDi::BpmnLabel* label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(Bpmn::BaseElement* sourceElement READ sourceElement WRITE setSourceElement NOTIFY sourceElementChanged)
    Q_PROPERTY(Bpmn::BaseElement* targetElement READ targetElement WRITE setTargetElement NOTIFY targetElementChanged)

public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<BpmnEdge>(Contants::BPMNDI_NS, Contants::BPMNDI_ELEMENT_BPMN_EDGE);
    }

    Q_INVOKABLE BpmnEdge(XmlDom::XmlTag *tag);
    ~BpmnEdge();

    /*!
     * \brief an optional label that is nested
     * when the edge has a visible text label with its own bounding box
     */
    BpmnLabel *label();
    void setLabel(BpmnLabel* value);


    /*!
     * \brief An optional reference to the edge’s source element
     * if it is different from the source inferred from the bpmnElement association
     */
    BaseElement *sourceElement();
    void setSourceElement(BaseElement* value);

    /*!
     * \brief An optional reference to the edge’s target element
     * if it is different from the target inferred from the bpmnElement association.
     */
    BaseElement *targetElement();
    void setTargetElement(BaseElement* value);

signals:
    void labelChanged();
    void sourceElementChanged();
    void targetElementChanged();

private:
    DECLARE_PRIVATE(BpmnEdge)
};
}
}
