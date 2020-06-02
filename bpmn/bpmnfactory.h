#pragma once
#include <xmldom/xmlmodelelement.h>
#include <xmldom/xmlmodeldocument.h>
#include <xmldom/xmlmodelsfactory.h>
#include <bpmn/bpmn_global.h>
#include <bpmn/baseelement.h>
#include <bpmn/extensionelements.h>
#include <QObject>
namespace Bpmn {
class BPMN_LIBRARY_EXPORT BpmnFactory : public XmlDom::XmlModelsFactory
{
    Q_OBJECT

public:
    explicit BpmnFactory();
    ~BpmnFactory();
    static BpmnFactory *instance();

protected:
    void registerNamespaces() override;
    void registerTypes(XmlDom::XmlModelElementTypeBuilder *typeBuilder) override;

public:
    template <class T>
    T* createExtensionElement(XmlDom::XmlModelDocument *doc, BaseElement *element){
        XmlDom::XmlTag *tag = createTag(qMetaTypeId<T*>(), doc);
        XmlDom::XmlModelElement *modelElement = doc->findModelElement(tag);
        element->extensionElements()->addExtension(modelElement);
        return qobject_cast<T*>(modelElement);
    }

};
}
