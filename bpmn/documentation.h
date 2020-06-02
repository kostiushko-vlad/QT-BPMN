/*****************************************************************************
* documentation.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Documentation)
/*!
 * \class Documentation
 * All BPMN elements that inherit from the BaseElement will have the capability, through the Documentation
 * element, to have one or more text descriptions of that element.
 */
class BPMN_LIBRARY_EXPORT Documentation : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString textFormat READ textFormat WRITE setTextFormat NOTIFY textFormatChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Documentation>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_DOCUMENTATION);
    }

    Q_INVOKABLE Documentation(XmlDom::XmlTag *tag);
    ~Documentation();

    /*!
     * \brief This attribute is used to capture
     * the text descriptions of a BPMN element
     */
    QString text() const;
    void setText(const QString &text);

    /*!
     * \brief This attribute identifies the format of the text.
     * It MUST follow the mime-type format. The default is "text/plain."
     */
    QString textFormat();
    void setTextFormat(const QString &format);

signals:
    void textChanged();
    void textFormatChanged();

private:
    DECLARE_PRIVATE(Documentation)
};
}
Q_DECLARE_METATYPE(Bpmn::Documentation*)
