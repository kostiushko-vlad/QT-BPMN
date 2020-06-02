/*****************************************************************************
* node.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/diagramelement.h>
#include <QObject>
namespace Bpmn {
namespace Di {
FORWARD_DECLARE_PRIVATE(Node)

/*!
 * \brief The Node class
 */
class BPMN_LIBRARY_EXPORT Node : public DiagramElement
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Node>(Contants::DI_NS, Contants::DI_ELEMENT_NODE);
    }

    Node(XmlDom::XmlTag *tag);
    ~Node();

public slots:

signals:

private:
    DECLARE_PRIVATE(Node)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Di::Node*)
