#include "parameters.h"
#include "bpmn/bpmnfactory.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class ParametersPrivate
{
public:
    ParametersPrivate(Parameters *p):q(p){}
    XmlDom::XmlChildListAttribute *parameters = nullptr;
    QQmlListProperty<Parameter> getParameters();
private:
    Parameters *q = nullptr;
};

QQmlListProperty<Parameter> ParametersPrivate::getParameters()
{
    QList<Parameter*> elements = Utils::toList<Parameter*>(parameters->elements());
    return QQmlListProperty<Parameter>(q, elements);
}

}

Parameters::Parameters(XmlDom::XmlTag *tag)
    : Extension(tag), d_ptr(new ParametersPrivate(this))
{
    d_ptr->parameters = attributeBuilder()->createChildListAttribute<Parameter>(this, &Parameters::parametersChanged);
}

Parameters::~Parameters()
{

}

QList<Parameter *> Parameters::parameters() const
{
    return d_ptr->parameters->elements<Parameter*>();
}

Parameter *Parameters::findParameter(const QString &name)
{
    for(Parameter *p : parameters()){
        if(p->name() == name)
            return p;
    }
    return nullptr;
}

}
}
#include "moc_parameters.cpp"
