/*****************************************************************************
* labelededge.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/edge.h>
#include <QObject>
namespace Bpmn {
namespace Di {
FORWARD_DECLARE_PRIVATE(LabeledEdge)

/*!
 * \brief The LabeledEdge class
 */
class BPMN_LIBRARY_EXPORT LabeledEdge : public Edge
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<LabeledEdge>(Contants::DI_NS, Contants::DI_ELEMENT_LABELED_EDGE);
    }

    Q_INVOKABLE LabeledEdge(XmlDom::XmlTag *tag);
    ~LabeledEdge();

public slots:

signals:

private:
    DECLARE_PRIVATE(LabeledEdge)
};
}
}
