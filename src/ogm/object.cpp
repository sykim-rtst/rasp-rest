#include <ara/rest/ogm/object.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    std::size_t Object::GetSize() const noexcept
    {
        return value_.size();
    }

    bool Object::IsEmpty() const noexcept
    {
        return value_.empty();
    }

    Object::FieldRange Object::GetFields() noexcept
    {
        return Object::FieldRange(value_.begin(), value_.end());
    }

    Object::ConstFieldRange Object::GetFields() const noexcept
    {
        return Object::ConstFieldRange(value_.cbegin(), value_.cend());
    }

    bool ogm::Object::HasField(std::string_view name) const noexcept
    {
        return std::any_of(value_.begin(), value_.end(), [&name](const Pointer<Field> &value) { return value->GetName() == name; });
    }

    Object::ValueType::iterator ogm::Object::Find(std::string_view name) noexcept
    {
        return std::find_if(value_.begin(), value_.end(), [&name](const Pointer<Field> &value) { return value->GetName() == name; });
    }

    Object::ValueType::const_iterator ogm::Object::Find(std::string_view name) const noexcept
    {
        return std::find_if(value_.cbegin(), value_.cend(), [&name](const Pointer<Field> &value) { return value->GetName() == name; });;
    }

    bool ogm::Object::Insert(Pointer<Field> &&field)
    {
        value_.push_back(std::move(field));

        return true;
    }

    Object::Iterator Object::Remove(Object::Iterator iterator)
    {
        return value_.erase(iterator);
    }

    std::pair<Object::Iterator, Pointer<Field>> Object::Release(Object::Iterator iterator)
    {
        Pointer<Field> oldValue = ogm::Copy(*iterator);
        return std::make_pair(Remove(iterator), std::move(oldValue));
    }

    Pointer<Field> Object::Replace(ValueType::iterator iterator, Pointer<Field> &&field)
    {
        Pointer<Field> oldValue = ogm::Copy(*iterator);
        value_.insert(value_.erase(iterator), std::move(field));
        return std::move(oldValue);
    }

    void ogm::Object::Clear()
    {
        value_.clear();
    }
}
}
}