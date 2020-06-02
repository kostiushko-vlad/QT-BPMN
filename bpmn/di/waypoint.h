/*****************************************************************************
* waypoint.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/dc/point.h>
#include <QObject>
namespace Bpmn {
namespace Di {
FORWARD_DECLARE_PRIVATE(Waypoint)

/*!
 * \brief The Waypoint class describes path way of the Edge
 */
class BPMN_LIBRARY_EXPORT Waypoint : public Dc::Point
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Waypoint>(Contants::DI_NS, Contants::DI_ELEMENT_WAYPOINT);
    }

    Q_INVOKABLE Waypoint(XmlDom::XmlTag *tag);
    ~Waypoint();

private:
    DECLARE_PRIVATE(Waypoint)
};
}
}
