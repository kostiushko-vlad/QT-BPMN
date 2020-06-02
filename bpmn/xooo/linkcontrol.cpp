#include "linkcontrol.h"
#include <bpmn/bpmnutils.h>

namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class LinkControlPrivate
{
public:
    QString source = "";
    QString name = "";

};
}

LinkControl::LinkControl(XmlDom::XmlTag* tag)
        : Artifact(tag), d_ptr(new LinkControlPrivate)
{
    // Find properties model, and connect model id changed with modelChanged signal
    connect(this, &LinkControl::propertyChanged, this, [=](const QString &property){
        if(property == "source") {
            emit sourceChanged();
        }
        if(property == "name") {
            emit nameChanged();
        }
    });
}

XOOO_EMPTY_DESCTRUCTOR_IMPLEMENTATION(LinkControl)


QString LinkControl::source()const
{
    QString source = BpmnUtils::elementPropertyValue(this, "source");
    return source;
}

void LinkControl::setSource(const QString &value)
{
    if(source() != value) {
        Bpmn::BpmnUtils::setElementProperty(this, "source", value);
        // When property changed internally
        emit sourceChanged();
    }
}

QString LinkControl::name() const
{
    QString name = BpmnUtils::elementPropertyValue(this, "name");
    return  name;
}
void LinkControl::setName(const QString& value)
{
    if(name() != value) {
        Bpmn::BpmnUtils::setElementProperty(this, "name", value);
        // When property changed internally
        emit nameChanged();
    }
}

}

}
