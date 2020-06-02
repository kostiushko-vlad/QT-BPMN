/*****************************************************************************
 * startevent.h
 *
 * Created: 13.04.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <bpmn/event.h>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(StartEvent)
/*!
 * \brief The Start Event indicates where a particular Process will start.
 */
class BPMN_LIBRARY_EXPORT StartEvent : public Event
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<StartEvent>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_START_EVENT);
    }
    Q_INVOKABLE StartEvent(XmlDom::XmlTag *tag);
    ~StartEvent();


private:
    DECLARE_PRIVATE(StartEvent)
};
}
Q_DECLARE_METATYPE(Bpmn::StartEvent*)
