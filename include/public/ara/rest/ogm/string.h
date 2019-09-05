#ifndef REST_STRING_H
#define REST_STRING_H

#include <ara/rest/ogm/value.h>
#include <ara/rest/support_type.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class String : public Value
    {
    public:
        /**
         * \brief   Type of this OGM node.
         *
         * \satisfy [SWS_REST_02140] Syntax Requirement for ara::rest::ogm::String::SelfType.
         */
        using SelfType = String;

        /**
         * \brief   Type of its parent in the OGM type hierarchy.
         *
         * \satisfy [SWS_REST_02141] Syntax Requirement for ara::rest::ogm::String::ParentType.
         */
        using ParentType = Value;

        /**
         * \brief   Type of its corresponding C++ data type.
         *
         * \satisfy [SWS_REST_02142] Syntax Requirement for ara::rest::ogm::String::ValueType.
         */
        using ValueType = ara::rest::String;

    public:
        /**
         * \brief   Returns its value as a C++ data type.
         *
         * \satisfy [SWS_REST_02146] Syntax Requirement for ara::rest::ogm::String::GetValue.
         */
        ValueType GetValue() const noexcept
        {
            return value_;
        }

        /**
         * \brief   Sets the current value from a C++ data type.
         *
         * \satisfy [SWS_REST_02147] Syntax Requirement for ara::rest::ogm::String::SetValue.
         */
        void SetValue(ValueType value) noexcept
        {
            value_ = value;
        }

    private:
        ValueType value_;

        /**
         * \brief   Connstructs an String.
         *
         * \satisfy [SWS_REST_02150] Syntax Requirement for Constructor.
         */
        String(ValueType value = ValueType{}) : Value(NodeType::String), value_(value) {};
    };

}
}
}

#endif //REST_STRING_H