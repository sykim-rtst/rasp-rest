#ifndef REST_FIELD_H
#define REST_FIELD_H

#include <ara/rest/ogm/node.h>
#include <ara/rest/ogm/value.h>
#include <ara/rest/support_type.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class Field : public Node, public Constructible<Field>, public Copyable<Field>
    {
    public:
        /**
          * \brief   Type of this OGM node.
          *
          * \satisfy [SWS_REST_02063] Syntax Requirement for ara::rest::ogm::Field::SelfType.
          */
        using SelfType = Field;

        /**
         * \brief   Type of its parent in the OGM type hierarchy.
         *
         * \satisfy [SWS_REST_02064] Syntax Requirement for ara::rest::ogm::Field::ParentType.
         */
        using ParentType = Node;

        using KeyType = ara::rest::String;

        using ValueType = Value;

        friend Constructible<Field>;

    public:
        /**
         * \brief   Creates a node of type SelfType(=Field).
         *
         * \satisfy [SWS_REST_02073] Syntax Requirement for ara::rest::ogm::Field::Make.
         */

        Field(Field&&) = default;
        Field& operator=(Field&&) = default;

    public:
        /**
         * \brief   Return the name of a Field. Fields names are immutable.
         *
         * \satisfy [SWS_REST_02068] Syntax Requirement for ara::rest::ogm::Field::GetName.
         */
        const KeyType& GetName() const noexcept
        {
            return name_;
        }

        /**
         * \brief   Returns the value represented by a Field.
         *
         * \satisfy [SWS_REST_02069] Syntax Requirement for ara::rest::ogm::Field::GetValue.
         */
        const ValueType& GetValue() const noexcept
        {
            return *value_;
        }

        /**
         * \brief   Returns the value represented by a Field.
         *
         * \satisfy [SWS_REST_02070] Syntax Requirement for ara::rest::ogm::Field::GetValue.
         */
        ValueType& GetValue() noexcept
        {
            return *value_;
        }

        /**
         * \brief   Sets a new value.
         *
         * \satisfy [SWS_REST_02071] Syntax Requirement for ara::rest::ogm::Field::SetValue.
         */
        void SetValue(Pointer<ValueType>&& value) noexcept
        {
            if (value_) value_.release();

            value_ = std::move(value);
        }

        /**
         * \brief   Sets a new value and returns the old one.
         *
         * \satisfy [SWS_REST_02072] Syntax Requirement for ara::rest::ogm::Field::ReplaceValue.
         */
        Pointer<ValueType> ReplaceValue(Pointer<ValueType>&& value) noexcept
        {
            Pointer<ValueType> oldValue = std::move(value_);
            value_ = std::move(value);

            return oldValue;
        }

    public:
        Field *Copy() const override
        {
            return new Field(name_, std::move(ogm::Copy(value_)));
        }

    public:
        KeyType name_;
        Pointer<ValueType> value_;

        /**
         * \brief   Constructs a Field.
         *
         * \satisfy [SWS_REST_02075] Syntax Requirement for Constructor.
         */
        Field(const std::string& name, Pointer<ValueType>&& value = Pointer<ValueType>())
                : Node(NodeType::Field), name_(name), value_(std::move(value)) {}
    };

}
}
}

#endif //REST_FIELD_H
