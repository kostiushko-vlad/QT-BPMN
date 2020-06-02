#include "textannotation.h"
namespace Bpmn {
// Private declaration
using namespace Internal;
namespace Internal {
class TextAnnotationPrivate
{
public:
    XmlDom::XmlAttribute* text = nullptr;
};
}

TextAnnotation::TextAnnotation(XmlDom::XmlTag *tag)
        : Artifact(tag), d_ptr(new TextAnnotationPrivate)
{
    d_ptr->text = attributeBuilder()->createAttribute("text", this, &TextAnnotation::textChanged);
}

TextAnnotation::~TextAnnotation()
{

}

QString TextAnnotation::text() const
{
    return d_ptr->text->toString();
}

void TextAnnotation::setText(const QString &value)
{
    d_ptr->text->setValue(value);
}
}

