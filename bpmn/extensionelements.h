/*****************************************************************************
 * extensionelements.h
 *
 * Created: 05.04.2019 2019 by Vladyslav Kostiushko
 *
 
 *
 *****************************************************************************/
#pragma once
#include <bpmn/baseelement.h>
#include <QObject>
namespace Bpmn {
class Extension;
FORWARD_DECLARE_PRIVATE(ExtensionElements)
class BPMN_LIBRARY_EXPORT ExtensionElements : public BaseElement
{
    Q_OBJECT
    Q_PRIVATE_PROPERTY(d_ptr, QQmlListProperty<Extension> elements READ getElements NOTIFY elementsChanged)
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<ExtensionElements>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_EXTENSION_ELEMENTS);
    }

    Q_INVOKABLE ExtensionElements(XmlDom::XmlTag *tag);
    ~ExtensionElements();

    // Functions for handling extension
    QList<Extension*> elements() const;
    QList<Extension *> elements(int typeId) const;
    void addExtension(XmlModelElement *element) const;
    template<class T>
    QList<T> elements() const{
        return toList<T>(elements(qMetaTypeId<T>()));
    }

    template<class T>
    T firstElement(){
        QList<T> elementList = elements<T>();
        if(!elementList.isEmpty())
            return elementList.first();
        return nullptr;
    }
signals:
    void elementAdded(Extension* extension);
    void elementsChanged();

private:
    DECLARE_PRIVATE(ExtensionElements)
};
}
Q_DECLARE_METATYPE(Bpmn::ExtensionElements*)
