#ifndef REST_SUPPORTED_H
#define REST_SUPPORTED_H

#include <memory>
#include <future>
#include <functional>
#include <string>

namespace ara
{
namespace rest
{

    template <typename T>
    using Pointer = std::unique_ptr<T>;

    template <typename T>
    using Task = std::future<T>;

    template <typename T>
    using Function = std::function<T>;

    using String = std::string;
    using StringView = std::string_view;

    using ErrorCode = std::error_code;

}
}

#endif //REST_SUPPORTED_H
