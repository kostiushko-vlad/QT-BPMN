/*****************************************************************************
* label.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/node.h>
#include <QObject>
#include <bpmn/bpmn_global.h>
namespace Bpmn {
namespace Dc {
class Bounds;
}
namespace Di {
FORWARD_DECLARE_PRIVATE(Label)
/*!
 * \brief The Label class
 */
class BPMN_LIBRARY_EXPORT Label : public Node
{
    Q_OBJECT
    Q_PROPERTY(Bpmn::Dc::Bounds* bounds READ bounds WRITE setBounds NOTIFY boundsChanged)
public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Label>(Contants::DI_NS, Contants::DI_ELEMENT_LABEL);
    }

    Q_INVOKABLE Label(XmlDom::XmlTag *tag);
    ~Label();

    Dc::Bounds *bounds();
    void setBounds(Dc::Bounds* value);

signals:
    void boundsChanged();

private:
    DECLARE_PRIVATE(Label)
};
}
}
