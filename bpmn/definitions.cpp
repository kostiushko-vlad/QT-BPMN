#include "definitions.h"
#include "bpmn/extension.h"
#include "bpmn/rootelement.h"
#include "bpmn_constants.h"
#include <bpmn/bpmndi/bpmndiagram.h>
#include <xmldom/xmlattributes.h>
#include <QUuid>
#include <QVariant>
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class DefinitionsPrivate
{
public:
    DefinitionsPrivate(Definitions *doc)
        :q(doc){}
    XmlDom::XmlAttribute* name = nullptr;
    XmlDom::XmlAttribute* targetNamespace = nullptr;
    XmlDom::XmlAttribute* expressionLanguage = nullptr;
    XmlDom::XmlAttribute* typeLanguage = nullptr;
    XmlDom::XmlAttribute* exporter = nullptr;
    XmlDom::XmlAttribute* exporterVersion = nullptr;
    XmlDom::XmlChildListAttribute* diagrams = nullptr;
    XmlDom::XmlChildListAttribute* rootElements = nullptr;

    QQmlListProperty<BpmnDi::BpmnDiagram> getDiagrams();
    QQmlListProperty<RootElement> getRootElements();


private:
    Definitions *q = nullptr;
};
}

Definitions::Definitions(XmlDom::XmlTag *tag)
    :BaseElement(tag), d_ptr(new DefinitionsPrivate(this))
{
    // Init attributes
    d_ptr->name = attributeBuilder()->createAttribute("name", this, &Definitions::nameChanged);
    d_ptr->targetNamespace = attributeBuilder()->createAttribute("targetNamespace", this, &Definitions::targetNamespaceChanged);
    d_ptr->expressionLanguage = attributeBuilder()->createAttribute("expressionLanguage", this, &Definitions::expressionLanguage);
    d_ptr->typeLanguage = attributeBuilder()->createAttribute("typeLanguage", this, &Definitions::typeLanguage);
    d_ptr->exporter = attributeBuilder()->createAttribute("exporter", this, &Definitions::exporter);
    d_ptr->exporterVersion = attributeBuilder()->createAttribute("exporterVersion", this, &Definitions::exporterVersion);
    d_ptr->diagrams = attributeBuilder()->createChildListAttribute<Bpmn::BpmnDi::BpmnDiagram>(this, &Definitions::diagramsChanged);
    d_ptr->rootElements = attributeBuilder()->createChildListAttribute<Bpmn::RootElement>(this, &Definitions::rootElementsChanged);
}

Definitions::~Definitions()
{

}

QString Definitions::name() const
{
    return d_ptr->name->toString();
}

QString Definitions::targetNamespace() const
{
    return d_ptr->targetNamespace->toString();
}

QString Definitions::expressionLanguage() const
{
    return d_ptr->expressionLanguage->toString();
}

QString Definitions::typeLanguage() const
{
    return d_ptr->typeLanguage->toString();
}

QString Definitions::exporter()
{
    return d_ptr->exporter->toString();
}

QString Definitions::exporterVersion()
{
    return d_ptr->exporterVersion->toString();
}

void Definitions::setName(const QString &value)
{
    d_ptr->name->setValue(value);
}

void Definitions::setTargetNamespace(const QString &value)
{
    d_ptr->targetNamespace->setValue(value);
}

void Definitions::setExpressionLanguage(const QString &value)
{
    d_ptr->expressionLanguage->setValue(value);
}

void Definitions::setTypeLanguage(const QString &value)
{
    d_ptr->typeLanguage->setValue(value);
}

void Definitions::setExporter(const QString &value)
{
    d_ptr->exporter->setValue(value);
}

void Definitions::setExporterVersion(const QString &value)
{
    d_ptr->exporterVersion->setValue(value);
}

QList<BpmnDi::BpmnDiagram *> Definitions::diagrams()
{
    return d_ptr->diagrams->elements<BpmnDi::BpmnDiagram*>();
}

QList<RootElement *> Definitions::rootElements()
{
    return d_ptr->rootElements->elements<RootElement*>();
}

QQmlListProperty<BpmnDi::BpmnDiagram> DefinitionsPrivate::getDiagrams()
{
    QList<BpmnDi::BpmnDiagram *> diagrams = q->diagrams();
    return QQmlListProperty<BpmnDi::BpmnDiagram>(q, diagrams);
}

QQmlListProperty<RootElement> DefinitionsPrivate::getRootElements()
{
    QList<RootElement *> elements = q->rootElements();
    return QQmlListProperty<RootElement>(q, elements);
}
}

#include "moc_definitions.cpp"
