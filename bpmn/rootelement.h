/*****************************************************************************
* rootelement.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(RootElement)
/*!
 * \brief RootElement is the abstract super class for all BPMN elements that are contained within Definitions. When
 * contained within Definitions, these elements have their own defined life-cycle and are not deleted with the deletion
 * of other elements.
 */
class BPMN_LIBRARY_EXPORT RootElement : public BaseElement
{
    Q_OBJECT   
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<RootElement>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_ROOT_ELEMENT);
    }

     RootElement(XmlDom::XmlTag *tag);
    ~RootElement();

private:
    DECLARE_PRIVATE(RootElement)
};
}
Q_DECLARE_METATYPE(Bpmn::RootElement*)
