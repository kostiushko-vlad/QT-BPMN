/*****************************************************************************
* baseelement_p.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

*
*****************************************************************************/
#pragma once
#include <bpmn/bpmn_global.h>
#include <xmldom/xmlattributes.h>
namespace Bpmn {
class Documentation;
class BaseElement;
class Definitions;
class Extension;
// Private declaration
namespace Internal {
class BPMN_LIBRARY_EXPORT BaseElementPrivate
{
     DECLARE_PUBLIC(BaseElement)
public:

    XmlDom::XmlAttribute *id = nullptr;
    XmlDom::XmlChildAttribute *documentation = nullptr;
    XmlDom::XmlChildAttribute *extensionElements = nullptr;

};
}
}

