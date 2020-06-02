/*****************************************************************************
 * callactivity.h
 *
 * Created: 17.04.2019 2019 by Vladyslav Kostiushko
 *
 * Copyright 2019 Xooo. All rights reserved.
 *
 *****************************************************************************/
#pragma once
#include <bpmn/activity.h>

#include <QObject>
namespace Bpmn {
namespace Xooo {
class Parameters;
class InputParameter;
class OutputParameter;
XOOO_FORWARD_DECLARE_PRIVATE(CallActivity)
class BPMN_LIBRARY_EXPORT CallActivity : public Activity
{
    Q_OBJECT
    Q_PROPERTY(QString modelId READ modelId WRITE setModelId NOTIFY modelChanged)

public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<CallActivity>(Contants::XOOO_BEHAVIORS_NS, Contants::XOOO_ELEMENT_CALL_ACTIVITY);
    }
    Q_INVOKABLE CallActivity(XmlDom::XmlTag *tag);

    ~CallActivity();

    /*!
     * \brief modelId
     * \return
     */
    QString modelId() const;
    void setModelId(const QString &value);


signals:
    void modelChanged();

private:
    XOOO_DECLARE_PRIVATE(CallActivity)
};
}
}
