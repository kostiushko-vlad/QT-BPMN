/*****************************************************************************
* incoming.h
*
* Created: 23.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Incoming)
class BPMN_LIBRARY_EXPORT Incoming : public BaseElement
{
    Q_OBJECT
public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Incoming>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_INCOMING);
    }

    Q_INVOKABLE Incoming(XmlDom::XmlTag *tag);
    ~Incoming();

public slots:

signals:

private:
    DECLARE_PRIVATE(Incoming)
};
}
