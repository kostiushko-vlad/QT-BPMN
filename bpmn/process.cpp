#include "process.h"
#include <bpmn/artifact.h>
#include <xmldom/xmlmodeldocument.h>
#include <xmldom/xmltag.h>
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class ProcessPrivate
{
public:
    ProcessPrivate(Process *proc) : q(proc){}
    XmlDom::XmlAttribute *isExecutable = nullptr;
    XmlDom::XmlChildListAttribute *artifacts = nullptr;
    QQmlListProperty<Artifact> getArtifacts();
private:
    Process *q = nullptr;
};


}

Process::Process(XmlDom::XmlTag *tag)
    : RootElement(tag), d_ptr(new ProcessPrivate(this))
{
    d_ptr->isExecutable = attributeBuilder()->createAttribute("isExecutable", this, &Process::isExecutableChanged);
    d_ptr->artifacts = attributeBuilder()->createChildListAttribute<Bpmn::Artifact>(this, &Process::artifactsChanged);
    if(id().isEmpty()) {
        setId(document()->nextUniqueId(tag->name()));
    }
}

Process::~Process()
{

}

bool Process::isExecutable()
{
    return d_ptr->isExecutable->value<bool>();
}

void Process::setIsExecutable(bool value)
{
    d_ptr->isExecutable->setValue(value);
}

QList<Artifact *> Process::artifacts() const
{
    return toList<Artifact*>(d_ptr->artifacts->elements());
}

QQmlListProperty<Artifact> ProcessPrivate::getArtifacts()
{
    QList<Artifact*> artifacts = q->artifacts();
    return QQmlListProperty<Artifact>(q, artifacts);
}

}
#include "moc_process.cpp"
