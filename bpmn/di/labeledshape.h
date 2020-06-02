/*****************************************************************************
* labeledshape.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/shape.h>
#include <QObject>
namespace Bpmn {
namespace Di {
FORWARD_DECLARE_PRIVATE(LabeledShape)

/*!
 * \brief LabeledShape represents a shape that owns a collection of labels
 */
class BPMN_LIBRARY_EXPORT LabeledShape : public Shape
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<LabeledShape>(Contants::DI_NS, Contants::DI_ELEMENT_LABELED_SHAPE);
    }

    Q_INVOKABLE LabeledShape(XmlDom::XmlTag *tag);
    ~LabeledShape();

public slots:

signals:

private:
    DECLARE_PRIVATE(LabeledShape)
};
}
}
