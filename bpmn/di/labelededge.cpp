#include "labelededge.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class LabeledEdgePrivate
{
public:

};
}

LabeledEdge::LabeledEdge(XmlDom::XmlTag *tag)
: Edge(tag), d_ptr(new LabeledEdgePrivate)
{

}

LabeledEdge::~LabeledEdge()
{

}
}
}

