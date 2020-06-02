#pragma once
#include <utils/xooodefs.h>
#include <bpmn/artifact.h>
namespace Bpmn {
namespace Xooo {
XOOO_FORWARD_DECLARE_PRIVATE(LinkControl)
class BPMN_LIBRARY_EXPORT LinkControl : public Artifact
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<LinkControl>(Contants::BPMN20_NS, Contants::XOOO_ELEMENT_LINK_CONTROL);
    }
    Q_INVOKABLE LinkControl(XmlDom::XmlTag* tag);
    ~LinkControl();

    QString source()const;
    QString name()const;

public slots:
    void setSource(const QString& value);
    void setName(const QString& value);

signals:
    void sourceChanged();
    void nameChanged();

private:
    XOOO_DECLARE_PRIVATE(LinkControl)
};
}
}
