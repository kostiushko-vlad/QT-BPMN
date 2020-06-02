#pragma once
#include <bpmn/artifact.h>
namespace Bpmn {
namespace Xooo {
XOOO_FORWARD_DECLARE_PRIVATE(DocumentControl)
class BPMN_LIBRARY_EXPORT DocumentControl : public Artifact
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<DocumentControl>(Contants::BPMN20_NS, Contants::XOOO_ELEMENT_DOCUMENT_CONTROL);
    }
    Q_INVOKABLE DocumentControl(XmlDom::XmlTag *tag);
    ~DocumentControl();

    QString source() const;
    void setSource(const QString &value);

signals:
    void sourceChanged();

private:
    XOOO_DECLARE_PRIVATE(DocumentControl)
};
}
}
