/*****************************************************************************
 * imagecontrol.h
 *
 * Created: 18.12.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/artifact.h>
namespace Bpmn {
namespace Xooo {
XOOO_FORWARD_DECLARE_PRIVATE(ImageControl)
class BPMN_LIBRARY_EXPORT ImageControl : public Artifact
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<ImageControl>(Contants::BPMN20_NS, Contants::XOOO_ELEMENT_IMAGE_CONTROL);
    }
    Q_INVOKABLE ImageControl(XmlDom::XmlTag *tag);
    ~ImageControl();

    QString source() const;
    void setSource(const QString &value);

signals:
    void sourceChanged();

private:
    XOOO_DECLARE_PRIVATE(ImageControl)
};
}
}
