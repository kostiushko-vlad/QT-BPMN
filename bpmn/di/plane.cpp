#include "plane.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class PlanePrivate
{
public:

};
}

Plane::Plane(XmlDom::XmlTag *tag)
: Node(tag), d_ptr(new PlanePrivate)
{

}

Plane::~Plane()
{

}
}
}

