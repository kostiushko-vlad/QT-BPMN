/*****************************************************************************
 * endevent.h
 *
 * Created: 13.04.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <bpmn/event.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(EndEvent)
/*!
 * \brief The  End Event indicates where a Process will end.
 */
class BPMN_LIBRARY_EXPORT EndEvent : public Event
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<EndEvent>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_END_EVENT);
    }
    Q_INVOKABLE EndEvent(XmlDom::XmlTag *tag);
    ~EndEvent();

private:
    DECLARE_PRIVATE(EndEvent)
};
}
Q_DECLARE_METATYPE(Bpmn::EndEvent*)
