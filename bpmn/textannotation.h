/*****************************************************************************
 * textannotation.h
 *
 * Created: 26.11.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <bpmn/artifact.h>
#include <QObject>
namespace Bpmn {
class BaseElement;
FORWARD_DECLARE_PRIVATE(TextAnnotation)
/*!
 * \brief Text Annotation objects can be used by the modeler to display additional information about a Process or attributes of
 * the objects within a BPMN Diagram
 */
class BPMN_LIBRARY_EXPORT TextAnnotation : public Artifact
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<TextAnnotation>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_TEXT_ANNOTATION);
    }
    Q_INVOKABLE TextAnnotation(XmlDom::XmlTag *tag);
    ~TextAnnotation();

    QString text() const;
    void setText(const QString &value);

signals:
    void textChanged();

private:
    DECLARE_PRIVATE(TextAnnotation)
};
}
Q_DECLARE_METATYPE(Bpmn::TextAnnotation*)

