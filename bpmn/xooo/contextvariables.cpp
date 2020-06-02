#include "contextvariables.h"
#include "bpmn/bpmnfactory.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class ContextVariablesPrivate
{
public:
    ContextVariablesPrivate(ContextVariables *p):q(p){}
    XmlDom::XmlChildListAttribute *variables = nullptr;
    QQmlListProperty<ContextVariable> getVariables();
private:
    ContextVariables *q = nullptr;

};
QQmlListProperty<ContextVariable> ContextVariablesPrivate::getVariables()
{
    QList<ContextVariable*> elements = Utils::toList<ContextVariable*>(variables->elements());
    return QQmlListProperty<ContextVariable>(q, elements);
}
}

ContextVariables::ContextVariables(XmlDom::XmlTag *tag)
    : Extension(tag), d_ptr(new ContextVariablesPrivate(this))
{
    d_ptr->variables = attributeBuilder()->createChildListAttribute<ContextVariable>(this, &ContextVariables::variablesChanged);
}

ContextVariables::~ContextVariables()
{

}

QList<ContextVariable *> ContextVariables::variables() const
{
    return d_ptr->variables->elements<ContextVariable*>();
}

ContextVariable *ContextVariables::findVariable(const QString &name)
{
    for(ContextVariable *v : variables()){
        if(v->name() == name)
            return v;
    }
    return nullptr;
}

}
}
#include "moc_contextvariables.cpp"
