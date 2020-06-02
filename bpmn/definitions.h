/*****************************************************************************
* definitions.h
*
* Created: 07.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
#include <QQmlListProperty>
namespace Bpmn {
namespace BpmnDi {
class BpmnDiagram;
}
class RootElement;
FORWARD_DECLARE_PRIVATE(Definitions)
/*!
 * \class Definitions class
 * is the outermost containing object for all BPMN elements.
 * It defines the scope of visibility and the namespace for all contained elements.
 * The interchange of BPMN files will always be through one or more Definitions.
 */
class BPMN_LIBRARY_EXPORT Definitions : public BaseElement
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString targetNamespace READ targetNamespace WRITE setTargetNamespace NOTIFY targetNamespaceChanged)
    Q_PROPERTY(QString expressionLanguage READ expressionLanguage WRITE setExpressionLanguage NOTIFY expressionLanguageChanged)
    Q_PROPERTY(QString typeLanguage READ typeLanguage WRITE setTypeLanguage NOTIFY typeLanguageChanged)
    Q_PROPERTY(QString exporter READ exporter WRITE setExporter NOTIFY exporterChanged)
    Q_PROPERTY(QString exporterVersion READ exporterVersion WRITE setExporterVersion NOTIFY exporterVersionChanged)
    Q_PRIVATE_PROPERTY(d_ptr, QQmlListProperty<Bpmn::BpmnDi::BpmnDiagram> diagrams READ getDiagrams NOTIFY diagramsChanged)
    Q_PRIVATE_PROPERTY(d_ptr, QQmlListProperty<Bpmn::RootElement> rootElements READ getRootElements NOTIFY rootElementsChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Definitions>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_DEFINITIONS);
    }
    Q_INVOKABLE Definitions(XmlDom::XmlTag *tag);
    ~Definitions();

    /*!
     * \brief The name of the Definition.
     */
    QString name() const;
    void setName(const QString &name);

    /*!
     * \brief This attribute identifies the namespace associated with the
     * Definition and follows the convention established by XML Schema.
     */
    QString targetNamespace() const;
    void setTargetNamespace(const QString &target);

    /*!
     * \brief This attribute identifies the formal Expression language used in
     * Expressions within the elements of this Definition. For example:
     * “http://www.w3.org/1999/XPath”
     */
    QString expressionLanguage() const;
    void setExpressionLanguage(const QString &language);

    /*!
     * \brief This attribute identifies the type system used by the elements of this Definition
     */
    QString typeLanguage() const;
    void setTypeLanguage(const QString &language);

    /*!
     * \brief This attribute identifies the tool that is exporting the bpmn model file
     */
    QString exporter();
    void setExporter(const QString &exporter);

    /*!
     * \brief This attribute identifies the version of the tool that is exporting the bpmn
     * model file.
     */
    QString exporterVersion();
    void setExporterVersion(const QString &exporter);

    /*!
     * \brief Lists the BPMNDiagrams that are contained within this Definitions
     * \return
     */
    QList<BpmnDi::BpmnDiagram *> diagrams();

    /*!
     * \brief List of RootElements
     * \return
     */
    QList<RootElement*> rootElements();

signals:
    void nameChanged();
    void targetNamespaceChanged();
    void expressionLanguageChanged();
    void typeLanguageChanged();
    void exporterChanged();
    void exporterVersionChanged();
    void diagramsChanged();
    void rootElementsChanged();

private:
    DECLARE_PRIVATE(Definitions)
};
}
Q_DECLARE_METATYPE(Bpmn::Definitions*)
