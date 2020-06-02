/*****************************************************************************
* association.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

*
*****************************************************************************/
#pragma once
#include <bpmn/artifact.h>
#include <QObject>
namespace Bpmn {
class BaseElement;
FORWARD_DECLARE_PRIVATE(Association)

/*!
 * \brief An Association is used to connect user-defined text (an Annotation) with a Flow Object
 */
class BPMN_LIBRARY_EXPORT Association : public Artifact
{
    Q_OBJECT
    Q_PROPERTY(AssociationDirection associationDirection READ associationDirection WRITE setAssociationDirection NOTIFY associationDirectionChanged)
    Q_PROPERTY(Bpmn::BaseElement* sourceRef READ sourceRef WRITE setSourceRef NOTIFY sourceRefChanged)
    Q_PROPERTY(Bpmn::BaseElement* targetRef READ targetRef WRITE setTargetRef NOTIFY targetRefChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Association>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_ASSOCIATION);
    }

    enum AssociationDirection {
        None = 0,
        One,
        Both
    };
    Q_ENUMS(AssociationDirections)

    Q_INVOKABLE Association(XmlDom::XmlTag *tag);
    ~Association();

    /*!
     * \brief AssociationDirection is an attribute that defines whether or not the
     * Association shows any directionality with an arrowhead. The default is
     * None (no arrowhead). A value of One means that the arrowhead SHALL
     * be at the Target Object. A value of Both means that there SHALL be an
     * arrowhead at both ends of the Association line.
     */
    AssociationDirection associationDirection() const;
    void setAssociationDirection(AssociationDirection direction);

    /*!
     * \brief The BaseElement that the Association is connecting from
     */
    BaseElement *sourceRef();
    void setSourceRef(BaseElement* source);

    /*!
     * \brief The BaseElement that the Association is connecting to.
     */
    BaseElement *targetRef();
    void setTargetRef(BaseElement* target);

signals:
    void associationDirectionChanged();
    void sourceRefChanged();
    void targetRefChanged();

private:
    DECLARE_PRIVATE(Association)
};
}
Q_DECLARE_METATYPE(Bpmn::Association*)
Q_DECLARE_METATYPE(Bpmn::Association::AssociationDirection)
