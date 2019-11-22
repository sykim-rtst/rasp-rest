#ifndef REST_ARRAY_H
#define REST_ARRAY_H

#include <vector>

#include <ara/rest/iterator.h>
#include <ara/rest/ogm/value.h>
#include <ara/rest/support_type.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class Array : public Value, public Constructible<Array>
    {
    public:
        /**
          * \brief   Type of this OGM node.
          *
          * \satisfy [SWS_REST_02037] Syntax Requirement for ara::rest::ogm::Array::SelfType.
          */
        using SelfType = Array;

        /**
         * \brief   Type of its parent in the OGM type hierarchy.
         *
         * \satisfy [SWS_REST_02038] Syntax Requirement for ara::rest::ogm::Array::ParentType.
         */
        using ParentType = Value;

        using ValueType = std::vector<Pointer<Value>>;

        /**
         * \brief   Value Iterator.
         *
         * \satisfy [SWS_REST_02039] Syntax Requirement for ara::rest::ogm::Array::Iterator.
         */
        using Iterator = ValueType::iterator;

        /**
         * \brief   Value Iterator.
         *
         * \satisfy [SWS_REST_02040] Syntax Requirement for ara::rest::ogm::Array::ConstIterator.
         */
        using ConstIterator = ValueType::const_iterator;

        /**
         * \brief   Iterator range.
         *
         * \satisfy [SWS_REST_02041] Syntax Requirement for ara::rest::ogm::Array::ValueRange.
         */
        using ValueRange = IteratorRange<Iterator>;

        /**
         * \brief   Iterator range.
         *
         * \satisfy [SWS_REST_02042] Syntax Requirement for ara::rest::ogm::Array::ConstValueRange.
         */
        using ConstValueRange = IteratorRange<ConstIterator>;

        friend Constructible<Array>;

    public:
        /**
         * \brief   Returns the number of elements.
         *
         * \satisfy [SWS_REST_02111] Syntax Requirement for ara::rest::ogm::Array::GetSize.
         */
        std::size_t GetSize() const noexcept;

        /**
         * \brief   Returns whether the Array holds no elements.
         *
         * \satisfy [SWS_REST_02112] Syntax Requirement for ara::rest::ogm::Array::IsEmpty.
         */
        bool IsEmpty() const noexcept;

        /**
         * \brief   Returns a Value at a specific index.
         *
         * \satisfy [SWS_REST_02048] Syntax Requirement for ara::rest::ogm::Array::GetValue.
         */
        Value & GetValue(std::size_t index) noexcept;

        /**
         * \brief   Returns a Value at a specific index.
         *
         * \satisfy [SWS_REST_02049] Syntax Requirement for ara::rest::ogm::Array::GetValue.
         */
        const Value & GetValue(std::size_t index) const noexcept;

        /**
         * \brief   Returns a range of values.
         *
         * \satisfy [SWS_REST_02050] Syntax Requirement for ara::rest::ogm::Array::GetValues.
         */
        ValueRange GetValues() noexcept;

        /**
         * \brief   Returns a range of values.
         *
         * \satisfy [SWS_REST_02051] Syntax Requirement for ara::rest::ogm::Array::GetValues.
         */
        ConstValueRange GetValues() const noexcept;

        /**
         * \brief   Appends a Value object to the array.
         *
         * \satisfy [SWS_REST_02052] Syntax Requirement for ara::rest::ogm::Array::Append.
         */
        void Append(std::unique_ptr<Value> &&value);

        /**
         * \brief   Inserts a Value at a specific position into the Array.
         *
         * \satisfy [SWS_REST_02053] Syntax Requirement for ara::rest::ogm::Array::Insert.
         */
        void Insert(Iterator iterator, std::unique_ptr<Value> &&value);

        /**
         * \brief   Removes value from the set.
         *
         * \satisfy [SWS_REST_02054] Syntax Requirement for ara::rest::ogm::Array::Remove.
         */
        Iterator Remove(Iterator iterator);

        /**
         * \brief   Similar to Remove but does not destroy the removed element.
         *
         * \satisfy [SWS_REST_02055] Syntax Requirement for ara::rest::ogm::Array::Release.
         */
        std::pair<Iterator, std::unique_ptr<Value>> Release(Iterator iterator);

        /**
         * \brief   Replaces an element by a new one without the destroying the old one.
         *
         * \satisfy [SWS_REST_02056] Syntax Requirement for ara::rest::ogm::Array::Replace.
         */
        std::unique_ptr<Value> Replace(Iterator iterator, std::unique_ptr<Value> &&value);

        /**
         * \brief   Removes all elements.
         *
         * \satisfy [SWS_REST_02057] Syntax Requirement for ara::rest::ogm::Array::Clear.
         */
        void Clear();

    protected:
        Array *Copy() const override
        {
            auto copyed = new Array();
            std::for_each(value_.begin(), value_.end(), [this, &copyed](const Pointer<Value> &value){
                copyed->Append(std::move(ogm::Copy(value)));
            });

            return copyed;
        }

    private:
        ValueType value_;

        /**
         * \brief   Connstructs an Array.
         *
         * \satisfy [SWS_REST_02060] Syntax Requirement for Constructor.
         */
        template <typename... Ts>
        Array(Pointer<Ts>&&... values) : Value(NodeType::Array)
        {
            int a[] = {0, (value_.push_back(std::move(values)), 0)...};
            static_cast<void>(a);
        };
    };

}
}
}

#endif //REST_ARRAY_H
