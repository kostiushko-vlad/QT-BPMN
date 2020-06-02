#include "activity.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ActivityPrivate
{
public:

};
}

Activity::Activity(XmlDom::XmlTag *tag)
        : FlowNode(tag), d_ptr(new ActivityPrivate)
{

}

Activity::~Activity()
{

}

}

