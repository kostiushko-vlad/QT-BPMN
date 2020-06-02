#include "flowelement.h"
#include "bpmn_constants.h"
#include <xmldom/xmlmodeldocument.h>
#include <xmldom/xmltag.h>
#include <bpmn/extensionelements.h>
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class FlowElementPrivate
{
public:
    XmlDom::XmlAttribute* name = nullptr;
//    XmlDom::XmlChildAttribute* properties = nullptr;
};
}

FlowElement::FlowElement(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new FlowElementPrivate)
{
    d_ptr->name = attributeBuilder()->createAttribute("name", this, &FlowElement::nameChanged);

    if(id().isEmpty()) {
        setId(document()->nextUniqueId(tag->name()));
    }
}

FlowElement::~FlowElement()
{

}

QString FlowElement::name() const
{
    return d_ptr->name->toString();
}

void FlowElement::setName(const QString &value)
{
    d_ptr->name->setValue(value);
}
}

