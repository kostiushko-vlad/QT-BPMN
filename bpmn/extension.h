/*****************************************************************************
* extension.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
#include <QVariant>
#include <QQmlListProperty>
namespace Bpmn {
class ExtensionDefinition;
FORWARD_DECLARE_PRIVATE(Extension)
/*!
 * \brief The Extension element binds/imports an ExtensionDefinition
 * and its attributes to a BPMN model definition
 */
class BPMN_LIBRARY_EXPORT Extension: public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Extension>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_EXTENSION);
    }

    Extension(XmlDom::XmlTag *tag);
    ~Extension();

    /*!
     * \brief The name of the extension. This is used as a namespace to
     * uniquely identify the extension content.
     */
    QString name() const;

protected:
    void setName(const QString &name);
signals:
    void nameChanged();

private:
    DECLARE_PRIVATE(Extension)
};
}
Q_DECLARE_METATYPE(Bpmn::Extension*)
