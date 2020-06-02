#include "waypoint.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class WaypointPrivate
{
public:

};
}
static int counter = 0;
Waypoint::Waypoint(XmlDom::XmlTag *tag)
: Point(tag), d_ptr(new WaypointPrivate)
{
    QString name = objectName() + QString::number(counter);
    tag->setObjectName(name);
    counter++;
}

Waypoint::~Waypoint()
{

}

}
}

