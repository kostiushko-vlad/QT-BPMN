#include "node.h"
namespace Bpmn {
namespace Di {
// Private declaration
using namespace Internal;
namespace Internal {
class NodePrivate
{
public:

};
}

Node::Node(XmlDom::XmlTag *tag)
: DiagramElement(tag), d_ptr(new NodePrivate)
{

}

Node::~Node()
{

}
}
}

