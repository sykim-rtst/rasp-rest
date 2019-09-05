#ifndef REST_VALUE_H
#define REST_VALUE_H

#include <ara/rest/ogm/node.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class Value : public Node
    {
    public:
        virtual ~Value() {}

    public:
        /**
         * \brief   Default Move Constructor & Assignment Operator.
         */
        Value(Value&&) = default;
        Value&operator=(Value&&) = default;

    protected:
        /**
         * \brief   Constructs an Value.
         *
         * \satisfy [SWS_REST_02158] Syntax Requirement for Constructor.
         */
        Value(NodeType type = NodeType::Undefined) : Node(type) {};
    };

}
}
}

#endif //REST_VALUE_H