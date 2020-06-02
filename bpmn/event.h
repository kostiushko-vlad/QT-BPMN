/*****************************************************************************
 * event.h
 *
 * Created: 29.03.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <bpmn/flownode.h>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Event)
/*!
 * \brief The Event class The Event element inherits the attributes and model associations of FlowElement (see Table 8.44), but adds no
additional attributes or model associations.
 */
class BPMN_LIBRARY_EXPORT Event : public FlowNode
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Event>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_BASE_EVENT);
    }
    Q_INVOKABLE Event(XmlDom::XmlTag *tag);
    ~Event();

private:
    DECLARE_PRIVATE(Event)
};
}
Q_DECLARE_METATYPE(Bpmn::Event*)
