#include "baseelement.h"
#include "baseelement_p.h"
#include "documentation.h"
#include "definitions.h"
#include "bpmn_constants.h"
#include "extension.h"
#include "extensionelements.h"
#include "xmldom/xmltag.h"
#include <QDebug>
using namespace XmlDom;
using namespace Bpmn::Internal;
namespace Bpmn {


BaseElement::BaseElement(XmlDom::XmlTag *tag)
    : XmlModelElement(tag), d_ptr(new BaseElementPrivate(this))
{
    // Init attributes
    d_ptr->id = attributeBuilder()->createAttribute("id", this, &BaseElement::idChanged);
    d_ptr->documentation = attributeBuilder()->createChildAttribute<Bpmn::Documentation>(this, &BaseElement::documentationChanged);
    d_ptr->extensionElements = attributeBuilder()->createChildAttribute<Bpmn::ExtensionElements>(this, &BaseElement::extensionElementsChanged);
    // Set object name for better debugging
    tag->setObjectName(id());
    setObjectName(id());
}

BaseElement::~BaseElement()
{
}

QString BaseElement::id() const
{
    return d_ptr->id->toString();
}

void BaseElement::setId(const QString &value)
{
    d_ptr->id->setValue(value);
}
Documentation *BaseElement::documentation()
{
    return qvariant_cast<Documentation*>(d_ptr->documentation->value());
}

ExtensionElements *BaseElement::extensionElements() const
{
    return d_ptr->extensionElements->element<ExtensionElements*>();
}

QString BaseElement::toString() const
{
    return d_ptr->id->toString();
}

Bpmn::BaseElement::operator QString() const
{
    return id();
}

}
