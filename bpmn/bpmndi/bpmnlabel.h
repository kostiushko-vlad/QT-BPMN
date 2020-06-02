/*****************************************************************************
* bpmnlabel.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/label.h>
#include <QObject>
namespace Bpmn {
namespace BpmnDi {
FORWARD_DECLARE_PRIVATE(BpmnLabel)
/*!
 * \brief BpmnLabel is a kind of label that depicts textual info about a BPMN element
 */
class BPMN_LIBRARY_EXPORT BpmnLabel : public Di::Label
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<BpmnLabel>(Contants::BPMNDI_NS, Contants::BPMNDI_ELEMENT_BPMN_LABEL);
    }

    Q_INVOKABLE BpmnLabel(XmlDom::XmlTag *tag);
    ~BpmnLabel();

private:
    DECLARE_PRIVATE(BpmnLabel)
};
}
}
Q_DECLARE_METATYPE(Bpmn::BpmnDi::BpmnLabel*)
