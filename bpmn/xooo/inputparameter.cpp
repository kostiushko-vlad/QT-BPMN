#include "inputparameter.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class InputParameterPrivate
{
public:

};
}

InputParameter::InputParameter(XmlDom::XmlTag *tag)
        : Parameter(tag), d_ptr(new InputParameterPrivate)
{

}

InputParameter::~InputParameter()
{

}
}
}

