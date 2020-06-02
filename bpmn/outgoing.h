/*****************************************************************************
* outgoing.h
*
* Created: 23.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Outgoing)
class BPMN_LIBRARY_EXPORT Outgoing : public BaseElement
{
    Q_OBJECT
public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Outgoing>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_OUTGOING);
    }

    Q_INVOKABLE Outgoing(XmlDom::XmlTag *tag);
    ~Outgoing();

public slots:

signals:

private:
    DECLARE_PRIVATE(Outgoing)
};
}
