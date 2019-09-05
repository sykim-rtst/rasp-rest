#include <ara/rest/ogm/array.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    std::size_t Array::GetSize() const noexcept
    {
        return value_.size();
    }

    bool Array::IsEmpty() const noexcept
    {
        return value_.empty();
    }

    Value &Array::GetValue(std::size_t index) noexcept
    {
        return *value_.at(index);
    }

    const Value &Array::GetValue(std::size_t index) const noexcept
    {
        return *value_.at(index);
    }

    Array::ValueRange Array::GetValues() noexcept
    {
        return Array::ValueRange(value_.begin(), value_.end());
    }

    Array::ConstValueRange Array::GetValues() const noexcept
    {
        return Array::ConstValueRange(value_.cbegin(), value_.cend());
    }

    void Array::Append(Pointer<Value> &&value)
    {
        value_.push_back(std::move(value));
    }

    void Array::Insert(Array::Iterator iterator, Pointer<Value> &&value)
    {
        value_.insert(iterator, std::move(value));
    }

    Array::Iterator Array::Remove(Array::Iterator iterator)
    {
        return value_.erase(iterator);
    }

    void Array::Clear()
    {
        value_.clear();
    }

}
}
}