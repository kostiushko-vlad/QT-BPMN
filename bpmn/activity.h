/*****************************************************************************
 * activity.h
 *
 * Created: 29.03.2019 2019 by Vladyslav Kostiushko
 *

 *
 *****************************************************************************/
#pragma once
#include <bpmn/flownode.h>
#include <QObject>
namespace Bpmn {
FORWARD_DECLARE_PRIVATE(Activity)
/*!
 * \brief The Activity class Activities represent points in a Process flow where work is performed.
 * They are the executable elements of a BPMN Process
 */
class BPMN_LIBRARY_EXPORT Activity : public FlowNode
{
    Q_OBJECT
public:
    static void registerType(XmlDom::XmlModelElementTypeBuilder *typeBuilder) {
        typeBuilder->registerType<Activity>(Contants::BPMN20_NS, Contants::BPMN_ELEMENT_ACTIVITY);
    }
    Q_INVOKABLE Activity(XmlDom::XmlTag *tag);
    ~Activity();

private:
    DECLARE_PRIVATE(Activity)
};
}
Q_DECLARE_METATYPE(Bpmn::Activity*)
