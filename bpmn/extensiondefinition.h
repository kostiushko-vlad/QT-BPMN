/*****************************************************************************
* extensiondefinition.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QVariant>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(ExtensionDefinition)
/*!
 * \brief The ExtensionDefinition class defines and groups additional attributes.
 */
class BPMN_LIBRARY_EXPORT ExtensionDefinition : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<ExtensionDefinition>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_EXTENSION_DEFINITION);
    }

    Q_INVOKABLE ExtensionDefinition(XmlDom::XmlTag *tag);
    ~ExtensionDefinition();

    /*!
     * \brief The name of the extension attribute.
     */
    QString name() const;
    void setName(const QString &name);

    /*!
     * \brief The name of the extension attribute.
     */
    QVariant value() const;
    void setValue(const QVariant &value);

signals:
    void valueChanged();
    void nameChanged();

private:
    DECLARE_PRIVATE(ExtensionDefinition)
};
}
Q_DECLARE_METATYPE(Bpmn::ExtensionDefinition*)
