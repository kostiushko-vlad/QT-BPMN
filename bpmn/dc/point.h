/*****************************************************************************
* point.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
namespace Dc {
FORWARD_DECLARE_PRIVATE(Point)

/*!
 * \brief A Point specifies a location in some x-y coordinate system
 */
class BPMN_LIBRARY_EXPORT Point : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Point>(Contants::DC_NS, Contants::DC_ELEMENT_POINT);
    }

    Q_INVOKABLE Point(XmlDom::XmlTag *tag);
    ~Point();

    qreal x();
    void setX(qreal value);

    qreal y();
    void setY(qreal value);

signals:
    void xChanged();
    void yChanged();

private:
    DECLARE_PRIVATE(Point)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Dc::Point*)
