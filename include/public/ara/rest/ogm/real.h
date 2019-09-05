#ifndef REST_REAL_H
#define REST_REAL_H

#include <ara/rest/ogm/value.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class Real : public Value
    {
    public:
        /**
         * \brief   Type of this OGM node.
         *
         * \satisfy [SWS_REST_02128] Syntax Requirement for ara::rest::ogm::Real::SelfType.
         */
        using SelfType = Real;

        /**
         * \brief   Type of its parent in the OGM type hierarchy.
         *
         * \satisfy [SWS_REST_02129] Syntax Requirement for ara::rest::ogm::Real::ParentType.
         */
        using ParentType = Value;

        /**
         * \brief   Type of its corresponding C++ data type.
         *
         * \satisfy [SWS_REST_02130] Syntax Requirement for ara::rest::ogm::Real::ValueType.
         */
        using ValueType = long double;

    public:
        /**
         * \brief   Returns its value as a C++ data type.
         *
         * \satisfy [SWS_REST_02134] Syntax Requirement for ara::rest::ogm::Real::GetValue.
         */
        ValueType GetValue() const noexcept
        {
            return value_;
        }

        /**
         * \brief   Sets the current value from a C++ data type.
         *
         * \satisfy [SWS_REST_02135] Syntax Requirement for ara::rest::ogm::Real::SetValue.
         */
        void SetValue(ValueType value) noexcept
        {
            value_ = value;
        }

    private:
        ValueType value_;

        /**
         * \brief   Connstructs an Real.
         *
         * \satisfy [SWS_REST_02138] Syntax Requirement for Constructor.
         */
        Real(ValueType value = ValueType{0}) : Value(NodeType::Real), value_(value) {};
    };

}
}
}

#endif //REST_REAL_H