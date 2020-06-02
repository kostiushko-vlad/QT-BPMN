#include "edge.h"
#include "waypoint.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class EdgePrivate
{
public:
    EdgePrivate(Edge *edge):q(edge){}
    XmlDom::XmlChildListAttribute* waypoints = nullptr;
private:
    Edge *q = nullptr;
};
}

Edge::Edge(XmlDom::XmlTag *tag)
    : DiagramElement(tag), d_ptr(new EdgePrivate(this))
{
    d_ptr->waypoints = attributeBuilder()->createChildListAttribute<Waypoint>(this, &Edge::waypointsChanged);
}

Edge::~Edge()
{

}

QList<Waypoint*> Edge::waypoints()
{
    return toList<Waypoint*>(d_ptr->waypoints->elements());
}

void Edge::clearWaypoints()
{
    d_ptr->waypoints->clear();
}

void Edge::addWaypoint(Waypoint *p)
{
    d_ptr->waypoints->append(p);
    emit waypointsChanged();
}
}
}
