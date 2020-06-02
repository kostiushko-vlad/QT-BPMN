/*****************************************************************************
* edge.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/diagramelement.h>
#include <QObject>
namespace Bpmn {
namespace Di {
class Waypoint;
FORWARD_DECLARE_PRIVATE(Edge)

/*!
 * \brief Edge is a diagram element that renders as a polyline,
 * connecting a source diagram element to a target diagram element,
 * and is positioned relative to the origin of the diagram
 */
class BPMN_LIBRARY_EXPORT Edge : public DiagramElement
{
    Q_OBJECT

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Edge>(Contants::DI_NS, Contants::DI_ELEMENT_EDGE);
    }

    Q_INVOKABLE Edge(XmlDom::XmlTag *tag);
    ~Edge();

    /*!
     * \brief An optional list of points relative to the origin of the nesting diagram
     * that specifies the connected line segments of the edge
     */
    QList<Waypoint*> waypoints();
    void clearWaypoints();

public slots:
    void addWaypoint(Waypoint *p);

signals:
    void waypointsChanged();

private:
    DECLARE_PRIVATE(Edge)
};
}
}
