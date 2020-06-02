#include "documentcontrol.h"
#include <bpmn/bpmnutils.h>
#include <QUrl>
namespace Bpmn {


namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class DocumentControlPrivate
{
public:
    QString source = "";

};
}

DocumentControl::DocumentControl(XmlDom::XmlTag *tag)
        : Artifact(tag), d_ptr(new DocumentControlPrivate)
{
    // Find properties model, and connect model id changed with modelChanged signal
    connect(this, &DocumentControl::propertyChanged, this, [=](const QString &property){
        if(property == "source") {
            emit sourceChanged();
        }
    });
}

XOOO_EMPTY_DESCTRUCTOR_IMPLEMENTATION(DocumentControl)


QString DocumentControl::source()const
{
    QString source = BpmnUtils::elementPropertyValue(this, "source");
    return source;
}
void DocumentControl::setSource(const QString &value)
{
    if(source() != value) {
        Bpmn::BpmnUtils::setElementProperty(this, "source", value);
        // When property changed internally
        emit sourceChanged();
    }
}


}

}
