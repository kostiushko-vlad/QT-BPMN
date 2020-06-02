#include "labeledshape.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class LabeledShapePrivate
{
public:

};
}

LabeledShape::LabeledShape(XmlDom::XmlTag *tag)
: Shape(tag), d_ptr(new LabeledShapePrivate)
{

}

LabeledShape::~LabeledShape()
{

}
}
}

