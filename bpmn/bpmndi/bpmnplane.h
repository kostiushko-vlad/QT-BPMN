/*****************************************************************************
* bpmnplane.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include<bpmn/di/plane.h>
#include <QObject>
namespace Bpmn {
namespace BpmnDi {
FORWARD_DECLARE_PRIVATE(BpmnPlane)

/*!
 * \brief A BPMNPlane is the BPMNDiagram container of BPMNShape and BPMNEdge.
 */
class BPMN_LIBRARY_EXPORT BpmnPlane : public Di::Plane
{
    Q_OBJECT
public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<BpmnPlane>(Contants::BPMNDI_NS, Contants::BPMNDI_ELEMENT_BPMN_PLANE);
    }

    Q_INVOKABLE BpmnPlane(XmlDom::XmlTag *tag);
    ~BpmnPlane();

private:
    DECLARE_PRIVATE(BpmnPlane)
};
}
}
Q_DECLARE_METATYPE(Bpmn::BpmnDi::BpmnPlane*)
