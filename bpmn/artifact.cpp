#include "artifact.h"
#include <xmldom/xmlmodeldocument.h>
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ArtifactPrivate
{
public:
    XmlDom::XmlChildAttribute *bounds = nullptr;

};
}

Artifact::Artifact(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new ArtifactPrivate)
{
    d_ptr->bounds = attributeBuilder()->createChildAttribute<Bpmn::Dc::Bounds>(this, &Artifact::boundsChanged);
    if(id().isEmpty()) {
        setId(document()->nextUniqueId(tag->name()));
    }
}

Artifact::~Artifact()
{

}

Dc::Bounds *Artifact::bounds()
{
    return d_ptr->bounds->element<Dc::Bounds*>();
}

void Artifact::setBounds(Dc::Bounds *value)
{
    d_ptr->bounds->setElement(value);
}
}

