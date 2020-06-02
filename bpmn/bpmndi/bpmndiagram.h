/*****************************************************************************
* bpmndiagram.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

*
*****************************************************************************/
#pragma once
#include <bpmn/di/diagram.h>
#include <QObject>
namespace Bpmn {
namespace BpmnDi {
class BpmnPlane;
FORWARD_DECLARE_PRIVATE(BpmnDiagram)

/*!
 * \brief BpmnDiagram is a kind of diagram that depicts all or part of a BPMN model.
 */
class BPMN_LIBRARY_EXPORT BpmnDiagram : public Di::Diagram
{
    Q_OBJECT
    Q_PROPERTY(Bpmn::BpmnDi::BpmnPlane* plane READ plane WRITE setPlane NOTIFY planeChanged)

public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<BpmnDiagram>(Contants::BPMNDI_NS, Contants::BPMNDI_ELEMENT_BPMN_DIAGRAM);
    }

    Q_INVOKABLE BpmnDiagram(XmlDom::XmlTag *tag);
    ~BpmnDiagram();

    /*!
     * \brief A BPMN plane element that is the container of all diagram elements in this diagram
     */
    BpmnPlane *plane();
    void setPlane(BpmnPlane* value);

signals:
    void planeChanged();

private:
    DECLARE_PRIVATE(BpmnDiagram)
};
}
}
Q_DECLARE_METATYPE(Bpmn::BpmnDi::BpmnDiagram*)
