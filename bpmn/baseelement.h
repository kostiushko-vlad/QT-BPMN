/*****************************************************************************
* baseelement.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

*
*****************************************************************************/
#pragma once
#include <bpmn/bpmn_global.h>
#include <bpmn/bpmn_constants.h>
#include <xmldom/xmlmodelelementtypebuilder.h>
#include <xmldom/xmlmodelelement.h>
#include <QDebug>
namespace Bpmn {
class ExtensionElements;
class Documentation;
FORWARD_DECLARE_PRIVATE(BaseElement)
/*!
 *  \class BaseElement
 * is the abstract super class for most BPMN elements. It provides the attributes id and documentation, which
 * other elements will inherit.
 */

class BPMN_LIBRARY_EXPORT BaseElement : public XmlDom::XmlModelElement
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Bpmn::Documentation* documentation READ documentation NOTIFY documentationChanged)
    Q_PROPERTY(Bpmn::ExtensionElements *extensionElements READ extensionElements NOTIFY extensionElementsChanged)

    Q_CLASSINFO("DefaultProperty", "extensionElements")

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<BaseElement>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_BASE_ELEMENT);
    }

    BaseElement(XmlDom::XmlTag *tag);
    virtual ~BaseElement() override;

    /*!
     * \brief This attribute is used to uniquely identify BPMN elements.
     */
    QString id() const;

    /*!
     * \brief Set indetificator
     * \param id new unique identificator
     */
    void setId(const QString &id);

    /*!
     * \brief This attribute is used to annotate the BPMN element,
     * such as descriptions and other documentation
     */
    Documentation *documentation();

    /*!
     * \brief extensionElements
     * \return
     */
    Bpmn::ExtensionElements *extensionElements() const;

    /*!
     * \brief toString string presentation of item
     * \return
     */
    virtual QString toString() const override;
    operator QString() const;

signals:
    void idChanged();
    void documentationChanged();
    void extensionElementsChanged();

private:
    //XmlDom::XmlChildAttribute* m_properties = nullptr;

    DECLARE_PRIVATE(BaseElement)
};
}
Q_DECLARE_METATYPE(Bpmn::BaseElement*)
