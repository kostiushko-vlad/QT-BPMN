/*****************************************************************************
* bounds.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
#include <QRectF>
namespace Bpmn {
namespace Dc {
FORWARD_DECLARE_PRIVATE(Bounds)

/*!
 * \brief Bounds specifies a rectangular area in some x-y coordinate system that is defined by a location (x and y) and a size (width
 * and height).
 */
class BPMN_LIBRARY_EXPORT Bounds : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Bounds>(Contants::DC_NS, Contants::DC_ELEMENT_BOUNDS);
    }

    Q_INVOKABLE Bounds(XmlDom::XmlTag *tag);
    ~Bounds();

    QRectF rect() const;

    qreal x() const;
    void setX(qreal value);

    qreal y() const;
    void setY(qreal value);

    qreal width() const;
    void setWidth(qreal value);

    qreal height() const;
    void setHeight(qreal value);

signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();

private:
    DECLARE_PRIVATE(Bounds)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Dc::Bounds*)
