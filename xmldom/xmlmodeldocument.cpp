#include "xmlmodeldocument.h"
#include "xmlmodelsfactory.h"
#include "xmlmodelelement.h"
namespace XmlDom {
// Private declaration
using namespace Internal;
namespace Internal {
class XmlModelDocumentPrivate
{
    DECLARE_PUBLIC(XmlModelDocument)
public:
    XmlModelElement *rootElement = nullptr;
    XmlModelsFactory *modelsFactory = nullptr;
    QHash<XmlTag*, XmlModelElement *> modelElements;
    bool loading = false;
    XmlModelElement *createModelElement(XmlTag *tag, bool recursive = true);
};

XmlModelElement *XmlModelDocumentPrivate::createModelElement(XmlTag *tag, bool recursive)
{
    // Create element
    XmlModelElement *element = modelsFactory->createModel(tag);

    // Add to elements list
    modelElements.insert(tag, element);
    return element;
}

}

XmlModelDocument::XmlModelDocument(XmlModelsFactory *modelsFactory, QObject *parent)
    : XmlDocument(parent), d_ptr(new XmlModelDocumentPrivate(this))
{
    setModelsFactory(modelsFactory);
}

XmlModelDocument::XmlModelDocument(const QString &filename, XmlModelsFactory *modelsFactory, QObject *parent)
    : XmlDocument(parent), d_ptr(new XmlModelDocumentPrivate(this))
{
    setModelsFactory(modelsFactory);

    // Load documents from file
    XmlDocument::load(filename);
}

XmlModelDocument::~XmlModelDocument()
{
    for(XmlTag *tag: d_ptr->modelElements.keys()) {
        XmlModelElement *element = d_ptr->modelElements.value(tag);
        d_ptr->modelElements.remove(tag);
        delete element;
    }
    d_ptr->modelElements.clear();
    d_ptr->rootElement = nullptr;
}

XmlModelElement *XmlModelDocument::rootElement()
{
    return d_ptr->rootElement;
}

QList<XmlModelElement *> XmlModelDocument::modelElements() const
{
    return d_ptr->modelElements.values();
}

XmlModelsFactory *XmlModelDocument::modelsFactory()
{
    return d_ptr->modelsFactory;
}

void XmlModelDocument::addTag(XmlTag *tag)
{
    // Add XmlTag to the document
    XmlDocument::addTag(tag);
    // Check if document contains namespace of tag
    QString ns = tag->namespaceUri();
    if(!namespaceUris().contains(ns)) {
        QString prefix = modelsFactory()->registeredNamespaces().value(ns);
        addNamespace(tag->namespaceUri(), prefix);
    }
    // Create model element
    XmlModelElement *element = d_ptr->createModelElement(tag);

    // Finilize when element added after loading
    if(!d_ptr->loading && element) {
        element->finilizeCreation();
    }

}

void XmlModelDocument::removeTag(XmlTag *tag)
{
    // Find model element
    XmlModelElement *element = d_ptr->modelElements.value(tag, nullptr);
    // Remove from list
    d_ptr->modelElements.remove(tag);
    // Delete element
    delete element;
    // Remove XMLTag
    XmlDocument::removeTag(tag);
}

XmlModelElement *XmlModelDocument::findModelElement(XmlTag *tag)
{
    XmlModelElement *element = d_ptr->modelElements.value(tag, nullptr);
    return element;
}

bool XmlModelDocument::load(QXmlStreamReader &xml)
{
    d_ptr->loading = true;
    // Delete root element if already exist
    if(rootElement()){
        delete d_ptr->rootElement;
        d_ptr->rootElement = nullptr;
    }

    // Load document
    bool result = XmlDocument::load(xml);

    // Init model elements after xml tags loaded
    if(result) {
        d_ptr->rootElement = findModelElement(rootTag());
    }

    reverseForeach(d_ptr->modelElements.values(), [=](XmlModelElement *element){
        element->finilizeCreation();
    });
    d_ptr->loading = false;
    return result;
}

void XmlModelDocument::setModelsFactory(XmlModelsFactory *modelsFactory)
{
    d_ptr->modelsFactory = modelsFactory;
}

}

