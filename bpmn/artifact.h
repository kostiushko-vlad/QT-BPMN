/*****************************************************************************
* artifact.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/dc/bounds.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Artifact)

/*!
 * \brief Provides modelers with the capability of showing additional information about
 *
 */
class BPMN_LIBRARY_EXPORT Artifact : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(Bpmn::Dc::Bounds* bounds READ bounds WRITE setBounds NOTIFY boundsChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Artifact>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_ARTIFACT);
    }

    Q_INVOKABLE Artifact(XmlDom::XmlTag *tag);
    ~Artifact();

    /*!
     * \brief Sinnce we use layouting Algoritm, we don't use BPMNDiagrams anymore
     * But artifacts can have free position on canvas. So this contains position
     * and size of an artifact
     */
    Dc::Bounds *bounds();
    void setBounds(Dc::Bounds* value);

signals:
    void boundsChanged();
private:
    DECLARE_PRIVATE(Artifact)
};
}
Q_DECLARE_METATYPE(Bpmn::Artifact*)
