/*****************************************************************************
* diagramelement.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
namespace Di {
FORWARD_DECLARE_PRIVATE(DiagramElement)

/*!
 * \brief TDiagramElement is the abstract super type of all elements in diagrams, including diagrams themselves. When contained
 * in a diagram, diagram elements are laid out relative to the diagram’s origin
 */
class BPMN_LIBRARY_EXPORT DiagramElement : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(Bpmn::BaseElement* bpmnElement READ bpmnElement WRITE setBpmnElement NOTIFY bpmnElementChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<DiagramElement>(Contants::DI_NS, Contants::DI_ELEMENT_DIAGRAM_ELEMENT);
    }

    Q_INVOKABLE DiagramElement(XmlDom::XmlTag *tag);
    ~DiagramElement();

    /*!
     * \brief a reference to a connecting BPMN element that this edge depicts.
     * Note that this reference is only optional for the specific case of a Data Association
     * connected to a Sequence Flow; in all other cases a referenced element must be provided
     */
    BaseElement *bpmnElement();
    void setBpmnElement(BaseElement* value);

signals:
    void bpmnElementChanged();

private:
    DECLARE_PRIVATE(DiagramElement)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Di::DiagramElement*)
