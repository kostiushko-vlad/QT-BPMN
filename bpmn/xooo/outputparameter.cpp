#include "outputparameter.h"
namespace Bpmn {
namespace Xooo {
// Private declaration
using namespace Internal;
namespace Internal {
class OutputParameterPrivate
{
public:

};
}

OutputParameter::OutputParameter(XmlDom::XmlTag *tag)
        : Parameter(tag), d_ptr(new OutputParameterPrivate)
{

}

OutputParameter::~OutputParameter()
{

}
}
}

