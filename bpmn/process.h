#pragma once
/*****************************************************************************
* process.h
*
* Created: 23.02.2019 2019 by Vladyslav Kostiushko
*

******************************************************************************/
#include <bpmn/rootelement.h>
#include <QObject>
namespace Bpmn {
class Artifact;
FORWARD_DECLARE_PRIVATE(Process)
class BPMN_LIBRARY_EXPORT Process : public RootElement
{
    Q_OBJECT
    Q_PROPERTY(bool isExecutable READ isExecutable WRITE setIsExecutable NOTIFY isExecutableChanged)
    Q_PRIVATE_PROPERTY(d_ptr, QQmlListProperty<Artifact> artifacts READ getArtifacts)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Process>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_PROCESS);
    }
    Q_INVOKABLE Process(XmlDom::XmlTag *tag);
    ~Process();

    bool isExecutable();
    void setIsExecutable(bool value);
    QList<Artifact *> artifacts() const;

signals:
    void isExecutableChanged();
    void artifactsChanged();

private:
    DECLARE_PRIVATE(Process)
};
}
Q_DECLARE_METATYPE(Bpmn::Process*)
