#ifndef OGM_UTIL_H
#define OGM_UTIL_H

#include <ara/rest/support_type.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    template <typename SelfType>
    class Constructible
    {
    public:
        template <typename... Ts>
        static Pointer<SelfType> Make(Ts&&...ts)
        {
            return Pointer<SelfType>(new SelfType(std::forward<Ts>(ts)...));
        }

    public:
        Constructible() = default;
    };

    template<typename T>
    Pointer<T> Copy(const T& object)
    {
        using base_type = typename T::base_type;
        static_assert(std::is_base_of<base_type, T>::value, "T object has to derived from T::base_type");
        auto ptr = static_cast<const base_type&>(object).Copy();
        return Pointer<T>(static_cast<T*>(ptr));
    }

    template<typename T>
    Pointer<T> Copy(const Pointer<T>& object)
    {
        return Copy(*object);
    }

    template<typename T>
    auto Copy(T* object) -> decltype(Copy(*object))
    {
        return Copy(*object);
    }

    template <typename BaseType>
    class Copyable
    {
    public:
        using base_type = BaseType;
        virtual  ~Copyable() = default;

    public:
        virtual BaseType* Copy() const = 0;

        template <typename DerivedType>
        friend Pointer<DerivedType> ogm::Copy(const DerivedType&);
    };

    template<typename T, typename U>
    Pointer<T> Cast(const U& object)
    {
        return Pointer<T>(dynamic_cast<T*>(ogm::Copy(object).get()));
    }

    template<typename T, typename U>
    Pointer<T> Cast(const Pointer<U>&  object)
    {
        return Pointer<T>(dynamic_cast<T*>(ogm::Copy(object).get()));
    }

}
}
}

#endif //OGM_UTIL_H