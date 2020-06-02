#include "callactivity.h"
#include <bpmn/extensionelements.h>
#include <bpmn/endevent.h>
#include <bpmn/startevent.h>
#include <bpmn/process.h>
#include <bpmn/bpmndi/bpmndiagram.h>
#include <bpmn/bpmndi/bpmnplane.h>
#include <bpmn/definitions.h>
#include <bpmn/bpmnfactory.h>
#include <bpmn/process.h>
#include <bpmn/xooo/parameters.h>
#include <bpmn/xooo/inputparameter.h>
#include <bpmn/xooo/outputparameter.h>
#include <xmldom/xmldocument.h>
#include <bpmn/xooo/properties.h>
#include <bpmn/xooo/property.h>
#include <bpmn/bpmnutils.h>
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class CallActivityPrivate
{
    XOOO_DECLARE_PUBLIC(CallActivity)
public:
};
}

CallActivity::CallActivity(XmlDom::XmlTag *tag)
    : Activity(tag), d_ptr(new CallActivityPrivate(this))
{

    // Find properties model, and connect model id changed with modelChanged signal
    connect(this, &CallActivity::propertyChanged, this, [=](const QString &property){
        if(property == "model_id") {
            emit modelChanged();
        }
    });
}

CallActivity::~CallActivity()
{

}

QString CallActivity::modelId() const
{
    QString id = BpmnUtils::elementPropertyValue(this, "model_id");
    return id;
}

void CallActivity::setModelId(const QString &value)
{
    if(modelId() != value) {
        Bpmn::BpmnUtils::setElementProperty(this, "model_id", value);
        // When property changed internally
        emit modelChanged();
    }
}




}
}

