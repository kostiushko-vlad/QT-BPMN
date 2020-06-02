#include "documentation.h"
#include "bpmn_constants.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class DocumentationPrivate
{
public:
    XmlDom::XmlAttribute* text;
    XmlDom::XmlAttribute* textFormat;
};
}

Documentation::Documentation(XmlDom::XmlTag *tag)
    : BaseElement(tag), d_ptr(new DocumentationPrivate)
{
    d_ptr->text = attributeBuilder()->createAttribute("text", this, &Documentation::textChanged);
    d_ptr->textFormat = attributeBuilder()->createAttribute("textFormat", this, &Documentation::textFormatChanged);
}

Documentation::~Documentation()
{

}

QString Documentation::text() const
{
    return d_ptr->text->toString();
}

void Documentation::setText(const QString &value)
{
    d_ptr->text->setValue(value);
}

QString Documentation::textFormat()
{
    return d_ptr->textFormat->toString();
}

void Documentation::setTextFormat(const QString &value)
{
    d_ptr->textFormat->setValue(value);
}
}

