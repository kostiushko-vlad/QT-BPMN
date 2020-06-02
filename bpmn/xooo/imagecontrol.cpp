#include "imagecontrol.h"
#include "properties.h"
#include "bpmn/extensionelements.h"
#include "property.h"
#include "bpmnfactory.h"
#include "bpmn/bpmnutils.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class ImageControlPrivate
{
public:

};

}

ImageControl::ImageControl(XmlDom::XmlTag *tag)
    : Artifact(tag), d_ptr(new ImageControlPrivate())
{
    // Find properties model, and connect model id changed with modelChanged signal
    connect(this, &DocumentControl::propertyChanged, this, [=](const QString &property){
        if(property == "source") {
            emit sourceChanged();
        }
    }, Qt::UniqueConnection);
}
XOOO_EMPTY_DESCTRUCTOR_IMPLEMENTATION(ImageControl)

QString ImageControl::source() const
{
    QString source = BpmnUtils::elementPropertyValue(this, "source");
    source.remove("\"");
    return source;
}

void ImageControl::setSource(const QString &value)
{
    QString val = value;
    if(source() != value) {
        Bpmn::BpmnUtils::setElementProperty(this, "source", value);
        // When property changed internally
        emit sourceChanged();
    }
}
}
}

