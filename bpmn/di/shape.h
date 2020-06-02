/*****************************************************************************
* shape.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/node.h>
#include <QObject>
namespace Bpmn {
namespace Dc {
class Bounds;
}
namespace Di {
FORWARD_DECLARE_PRIVATE(Shape)

/*!
 * \brief Shape is a diagram element with given bounds
 * that is laid out relative to the origin of the diagram
 */
class BPMN_LIBRARY_EXPORT Shape : public Node
{
    Q_OBJECT
    Q_PROPERTY(Bpmn::Dc::Bounds* bounds READ bounds WRITE setBounds NOTIFY boundsChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Shape>(Contants::DI_NS, Contants::DI_ELEMENT_SHAPE);
    }

    Q_INVOKABLE Shape(XmlDom::XmlTag *tag);
    ~Shape();

    /*!
     * \brief The optional bounds of the shape relative to the origin of its nesting plane
     */
    Dc::Bounds* bounds();
    void setBounds(Dc::Bounds* value);

signals:
    void boundsChanged();
private:
    DECLARE_PRIVATE(Shape)
};
}
}
