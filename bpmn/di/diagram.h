/*****************************************************************************
* diagram.h
*
* Created: 14.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/rootelement.h>
#include <QObject>
namespace Bpmn {
namespace Di {
FORWARD_DECLARE_PRIVATE(Diagram)

/*!
 * \brief Diagram is an abstract container of a graph of diagram elements. Diagrams are diagram elements with an origin point in
 * the x-y coordinate system. Their elements are laid out relative to their origin point.
 */
class BPMN_LIBRARY_EXPORT Diagram : public RootElement
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qreal resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Diagram>(Contants::DI_NS, Contants::DI_ELEMENT_DIAGRAM);
    }

    Q_INVOKABLE Diagram(XmlDom::XmlTag *tag);
    ~Diagram();

    /*!
     * \brief The name of the diagram
     */
    QString name();
    void setName(QString value);

    /*!
     * \brief The resolution of the diagram expressed in user units per inch
     */
    qreal resolution();
    void setResolution(qreal value);


signals:
    void nameChanged();
    void resolutionChanged();

private:
    DECLARE_PRIVATE(Diagram)
};
}
}
Q_DECLARE_METATYPE(Bpmn::Di::Diagram*)
