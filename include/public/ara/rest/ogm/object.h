#ifndef REST_OBJECT_H
#define REST_OBJECT_H

#include <vector>

#include <ara/rest/iterator.h>
#include <ara/rest/ogm/value.h>
#include <ara/rest/ogm/field.h>
#include <ara/rest/support_type.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class Object : public Value
    {
    public:
        /**
         * \brief   Type of this OGM node.
         *
         * \satisfy [SWS_REST_02140] Syntax Requirement for ara::rest::ogm::Object::SelfType.
         */
        using SelfType = Object;

        /**
         * \brief   Type of its parent in the OGM type hierarchy.
         *
         * \satisfy [SWS_REST_02141] Syntax Requirement for ara::rest::ogm::Object::ParentType.
         */
        using ParentType = Value;

        using ValueType = std::vector<Pointer<Field>>;

        /**
         * \brief   Value Iterator.
         *
         * \satisfy [SWS_REST_02104] Syntax Requirement for ara::rest::ogm::Object::Iterator.
         */
        using Iterator = ValueType::iterator;

        /**
         * \brief   Value Iterator.
         *
         * \satisfy [SWS_REST_02105] Syntax Requirement for ara::rest::ogm::Object::ConstIterator.
         */
        using ConstIterator = ValueType::const_iterator;

        /**
         * \brief   Iterator range.
         *
         * \satisfy [SWS_REST_02106] Syntax Requirement for ara::rest::ogm::Object::FieldRange.
         */
        using FieldRange = IteratorRange<Iterator>;

        /**
         * \brief   Iterator range.
         *
         * \satisfy [SWS_REST_02107] Syntax Requirement for ara::rest::ogm::Object::ConstFieldRange.
         */
        using ConstFieldRange = IteratorRange<ConstIterator>;

    public:
        /**
         * \brief   Returns the number of elements.
         *
         * \satisfy [SWS_REST_02111] Syntax Requirement for ara::rest::ogm::Object::GetSize.
         */
        std::size_t GetSize() const noexcept;

        /**
         * \brief   Returns whether the object holds no elements.
         *
         * \satisfy [SWS_REST_02112] Syntax Requirement for ara::rest::ogm::Object::IsEmpty.
         */
        bool IsEmpty() const noexcept;

        /**
         * \brief   Returns a range of fields.
         *
         * \satisfy [SWS_REST_02113] Syntax Requirement for ara::rest::ogm::Object::GetFields.
         */
        FieldRange GetFields() noexcept;

        /**
         * \brief   Returns a range of fields.
         *
         * \satisfy [SWS_REST_02114] Syntax Requirement for ara::rest::ogm::Object::GetFields.
         */
        ConstFieldRange GetFields() const noexcept;

        /**
         * \brief   Checks whether a field of a given name exists.
         *
         * \satisfy [SWS_REST_02115] Syntax Requirement for ara::rest::ogm::Object::HasField.
         */
        bool HasField(std::string_view name) const noexcept;

        /**
         * \brief   Searches for a field of the given name. If the given field name is not found, the return value will be equal to GetFields().end().
         *
         * \satisfy [SWS_REST_02116] Syntax Requirement for ara::rest::ogm::Object::Find.
         */
        Iterator Find(std::string_view name) noexcept;

        /**
         * \brief   Searches for a field of the given name. If the given field name is not found, the return value will be equal to GetFields().end().
         *
         * \satisfy [SWS_REST_02117] Syntax Requirement for ara::rest::ogm::Object::Find.
         */
        ConstIterator Find(std::string_view name) const noexcept;

        /**
         * \brief   Inserts a field into the object.
         *
         * \satisfy [SWS_REST_02118] Syntax Requirement for ara::rest::ogm::Object::Insert.
         */
        bool Insert(Pointer<Field> &&field);

        /**
         * \brief   Removes value from the set.
         *
         * \satisfy [SWS_REST_02119] Syntax Requirement for ara::rest::ogm::Object::Remove.
         */
        Iterator Remove(Iterator iterator);

        /**
         * \brief   Similar to Remove but does not destroy the removed element.
         *
         * \satisfy [SWS_REST_02120] Syntax Requirement for ara::rest::ogm::Object::Release.
         */
        // std::pair<Iterator, Pointer<Field>> Release(Iterator iterator);

        /**
         * \brief   Replaces an element by a new one without the destroying the old one.
         *
         * \satisfy [SWS_REST_02121] Syntax Requirement for ara::rest::ogm::Object::Replace.
         */
        // Pointer<Field> Replace(Iterator iterator, Pointer<Field> &&field);

        /**
         * \brief   Removes all elements.
         *
         * \satisfy [SWS_REST_02122] Syntax Requirement for ara::rest::ogm::Object::Clear.
         */
        void Clear();

    private:
        ValueType value_;

        /**
         * \brief   Connstructs an Object.
         *
         * \satisfy [SWS_REST_02125] Syntax Requirement for Constructor.
         */
        template <typename... Ts>
        Object(Pointer<Ts>&&... fields) : Value(NodeType::Object)
        {
            int a[] = {0, (value_.push_back(std::move(fields)), 0)...};
            static_cast<void>(a);
        }
    };

}
}
}

#endif //REST_OBJECT_H