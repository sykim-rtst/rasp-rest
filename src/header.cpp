#include <ara/rest/header.h>

namespace ara
{
namespace rest
{

    /**
     * ara::rest::RequestHeader Constructors
     */
    RequestHeader::RequestHeader(ara::rest::RequestMethod method, ara::rest::Uri uri)
            : method_(method), uri_(uri), status_(StatusCode::HTTP_OK)
    {

    }

    /**
     * ara::rest::RequestHeader Member Functions
     */
    RequestMethod ara::rest::RequestHeader::GetMethod() const
    {
        return method_;
    }

    void ara::rest::RequestHeader::SetMethod(RequestMethod method)
    {
        method_ = method;
    }

    const Uri &ara::rest::RequestHeader::GetUri() const
    {
        return uri_;
    }

    void ara::rest::RequestHeader::SetUri(const Uri &uri)
    {
        uri_ = uri;
    }

    StatusCode ara::rest::RequestHeader::GetStatus() const
    {
        return status_;
    }

    void ara::rest::RequestHeader::SetStatus(StatusCode code) noexcept
    {
        status_ = code;
    }

    /**
     * ara::rest::ReplyHeader Constructors
     */
    ReplyHeader::ReplyHeader(ara::rest::Uri uri, int status)
            : uri_(uri), status_(status)
    {

    }

    ReplyHeader::ReplyHeader(ara::rest::Uri uri, StatusCode status)
            : uri_(uri), status_(status)
    {

    }

    /**
     * ara::rest::ReplyHeader Member Functions
     */

    const Uri &ara::rest::ReplyHeader::GetUri() const
    {
        return uri_;
    }

    void ara::rest::ReplyHeader::SetUri(const Uri &uri)
    {
        uri_ = uri;
    }

    StatusCode ara::rest::ReplyHeader::GetStatus() const
    {
        return status_;
    }

    void ara::rest::ReplyHeader::SetStatus(StatusCode code) noexcept
    {
        status_ = code;
    }

}
}