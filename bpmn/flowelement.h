/*****************************************************************************
* flowelement.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(FlowElement)
/*!
 * \brief The FlowElement class
 */
class BPMN_LIBRARY_EXPORT FlowElement : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<FlowElement>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_FLOW_ELEMENT);
    }

    Q_INVOKABLE FlowElement(XmlDom::XmlTag *tag);
    ~FlowElement();

    /*!
     * \brief The descriptive name of the element.
     */
    QString name() const;
    void setName(const QString &name);

signals:
    void nameChanged();

private:
    DECLARE_PRIVATE(FlowElement)
};
}
Q_DECLARE_METATYPE(Bpmn::FlowElement*)
