/*****************************************************************************
* bpmnshape.h
*
* Created: 15.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/di/labeledshape.h>
namespace Bpmn {
namespace BpmnDi {
FORWARD_DECLARE_PRIVATE(BpmnShape)

/*!
 * \brief BPMNShape is a kind of shape that can depict a BPMN model element.
 */
class BPMN_LIBRARY_EXPORT BpmnShape : public Di::LabeledShape
{
    Q_OBJECT
    Q_PROPERTY(bool isHorizontal READ isHorizontal WRITE setIsHorizontal NOTIFY isHorizontalChanged)
    Q_PROPERTY(bool isExpanded READ isExpanded WRITE setIsExpanded NOTIFY isExpandedChanged)
    Q_PROPERTY(bool isMarkerVisible READ isMarkerVisible WRITE setIsMarkerVisible NOTIFY isMarkerVisibleChanged)

public:

    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<BpmnShape>(Contants::BPMNDI_NS, Contants::BPMNDI_ELEMENT_BPMN_SHAPE);
    }

    Q_INVOKABLE BpmnShape(XmlDom::XmlTag *tag);
    ~BpmnShape();

    /*!
     * \brief An optional attribute that should be used only for Pools and Lanes.
     * It determines if it should be depicted horizontally (true) or vertically (false).
     */
    bool isHorizontal();
    void setIsHorizontal(bool value);

    /*!
     * \brief An optional attribute that should be used only for CallActivities.
     * It determines if it should be depicted expanded(true) or collapsed (false).
     */
    bool isExpanded();
    void setIsExpanded(bool value);

    /*!
     * \brief An optional attribute that should be used only for Exclusive Gateway.
     * It determines if the marker should be depicted on the shape (true) or not (false).
     */
    bool isMarkerVisible();
    void setIsMarkerVisible(bool value);

signals:
    void isHorizontalChanged();
    void isExpandedChanged();
    void isMarkerVisibleChanged();

private:
    DECLARE_PRIVATE(BpmnShape)
};
}
}
