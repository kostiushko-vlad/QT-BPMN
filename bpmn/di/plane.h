/*****************************************************************************
* plane.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/node.h>
#include <QObject>
namespace Bpmn {
namespace Di {
FORWARD_DECLARE_PRIVATE(Plane)

/*!
 * \brief The Plane class
 */
class BPMN_LIBRARY_EXPORT Plane : public Node
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Plane>(Contants::DI_NS, Contants::DI_ELEMENT_PLANE);
    }

    Q_INVOKABLE Plane(XmlDom::XmlTag *tag);
    ~Plane();
private:
    DECLARE_PRIVATE(Plane)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Di::Plane*)
