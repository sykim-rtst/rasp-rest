#ifndef REST_INT_H
#define REST_INT_H

#include <ara/rest/ogm/value.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class Int : public Value
    {
    public:
        /**
         * \brief   Type of this OGM node.
         *
         * \satisfy [SWS_REST_02078] Syntax Requirement for ara::rest::ogm::Int::SelfType.
         */
        using SelfType = Int;

        /**
         * \brief   Type of its parent in the OGM type hierarchy.
         *
         * \satisfy [SWS_REST_02079] Syntax Requirement for ara::rest::ogm::Int::ParentType.
         */
        using ParentType = Value;

        /**
         * \brief   Type of its corresponding C++ data type.
         *
         * \satisfy [SWS_REST_02080] Syntax Requirement for ara::rest::ogm::Int::ValueType.
         */
        using ValueType = std::int64_t;

    public:
        /**
         * \brief   Returns its value as a C++ data type.
         *
         * \satisfy [SWS_REST_02084] Syntax Requirement for ara::rest::ogm::Int::GetValue.
         */
        ValueType GetValue() const noexcept
        {
            return value_;
        }

        /**
         * \brief   Sets the current value from a C++ data type.
         *
         * \satisfy [SWS_REST_02085] Syntax Requirement for ara::rest::ogm::Int::SetValue.
         */
        void SetValue(ValueType value) noexcept
        {
            value_ = value;
        }

    private:
        ValueType value_;

        /**
         * \brief   Connstructs an Int.
         *
         * \satisfy [SWS_REST_02088] Syntax Requirement for Constructor.
         */
        Int(ValueType value = ValueType{0}) : Value(NodeType::Int), value_(value) {};
    };

}
}
}


#endif //REST_INT_H
