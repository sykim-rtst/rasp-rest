#ifndef REST_HEADER_H
#define REST_HEADER_H

#include <string_view>

#include <ara/rest/endpoint.h>
#include <ara/rest/uri.h>

namespace ara
{
namespace rest
{
    class StatusCode {
    public:
        enum Code : uint16_t
        {
            /** Informational Response */
            HTTP_CONTINUE                        = 100,
            HTTP_SWITCHING_PROTOCOLS             = 101,
            HTTP_PROCESSING                      = 102,
            HTTP_EARLY_HINTS                     = 103,

            /** Success */
            HTTP_OK                              = 200,
            HTTP_CREATED                         = 201,
            HTTP_ACCEPTED                        = 202,
            HTTP_NONAUTHORITATIVE                = 203,
            HTTP_NO_CONTENT                      = 204,
            HTTP_RESET_CONTENT                   = 205,
            HTTP_PARTIAL_CONTENT                 = 206,
            HTTP_MULTI_STATUS                    = 207,
            HTTP_ALREADY_REPORTED                = 208,
            HTTP_IM_USED                         = 226,

            /** Redirection */
            HTTP_MULTIPLE_CHOICES                = 300,
            HTTP_MOVED_PERMANENTLY               = 301,
            HTTP_FOUND                           = 302,
            HTTP_SEE_OTHER                       = 303,
            HTTP_NOT_MODIFIED                    = 304,
            HTTP_USE_PROXY                       = 305,
            HTTP_TEMPORARY_REDIRECT              = 307,
            HTTP_PERMANENT_REDIRECT              = 308,

            /** Client Error */
            HTTP_BAD_REQUEST                     = 400,
            HTTP_UNAUTHORIZED                    = 401,
            HTTP_PAYMENT_REQUIRED                = 402,
            HTTP_FORBIDDEN                       = 403,
            HTTP_NOT_FOUND                       = 404,
            HTTP_METHOD_NOT_ALLOWED              = 405,
            HTTP_NOT_ACCEPTABLE                  = 406,
            HTTP_PROXY_AUTHENTICATION_REQUIRED   = 407,
            HTTP_REQUEST_TIMEOUT                 = 408,
            HTTP_CONFLICT                        = 409,
            HTTP_GONE                            = 410,
            HTTP_LENGTH_REQUIRED                 = 411,
            HTTP_PRECONDITION_FAILED             = 412,
            HTTP_REQUEST_ENTITY_TOO_LARGE        = 413,
            HTTP_REQUEST_URI_TOO_LONG            = 414,
            HTTP_UNSUPPORTED_MEDIA_TYPE          = 415,
            HTTP_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
            HTTP_EXPECTATION_FAILED              = 417,
            HTTP_IM_A_TEAPOT                     = 418,
            HTTP_ENCHANCE_YOUR_CALM              = 420,
            HTTP_MISDIRECTED_REQUEST             = 421,
            HTTP_UNPROCESSABLE_ENTITY            = 422,
            HTTP_LOCKED                          = 423,
            HTTP_FAILED_DEPENDENCY               = 424,
            HTTP_UPGRADE_REQUIRED                = 426,
            HTTP_PRECONDITION_REQUIRED           = 428,
            HTTP_TOO_MANY_REQUESTS               = 429,
            HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
            HTTP_UNAVAILABLE_FOR_LEGAL_REASONS   = 451,

            /** Server Error */
            HTTP_INTERNAL_SERVER_ERROR           = 500,
            HTTP_NOT_IMPLEMENTED                 = 501,
            HTTP_BAD_GATEWAY                     = 502,
            HTTP_SERVICE_UNAVAILABLE             = 503,
            HTTP_GATEWAY_TIMEOUT                 = 504,
            HTTP_VERSION_NOT_SUPPORTED           = 505,
            HTTP_VARIANT_ALSO_NEGOTIATES         = 506,
            HTTP_INSUFFICIENT_STORAGE            = 507,
            HTTP_LOOP_DETECTED                   = 508,
            HTTP_NOT_EXTENDED                    = 510,
            HTTP_NETWORK_AUTHENTICATION_REQUIRED = 511
        };

        StatusCode() = default;
        constexpr StatusCode(Code code) : code_(code) { }
        constexpr StatusCode(int code) : code_(static_cast<Code>(code)) { }

        String ToString()
        {
            return std::to_string(static_cast<uint16_t>(code_));
        }

        static const String ToString(StatusCode code)
        {
            return std::to_string(static_cast<uint16_t>(code.code_));
        }

    private:
        Code code_;
    };


    class RequestHeader
    {
    public:
        /**
         * \brief   Default-constructs a RequestHeader.
         */
        RequestHeader() = default;

        /**
         * \brief
         */
        RequestHeader(RequestMethod method, Uri uri);

    public:
        /**
         * \brief   Returns the request method.
         *
         * \satisfy [SWS_REST_02176] Syntax Requirement for ara::rest::RequestHeader::GetMethod.
         */
        RequestMethod GetMethod() const;

        /**
         * \brief   Allows to set the request method.
         *
         * \satisfy [SWS_REST_02177] Syntax Requirement for ara::rest::RequestHeader::SetMethod.
         */
        void SetMethod(RequestMethod method);

        /**
         * \brief   Returns a Uri.
         *
         * \satisfy [SWS_REST_02178] Syntax Requirement for ara::rest::RequestHeader::GetUri.
         */
        const Uri & GetUri() const;

        /**
         * \brief   Allows to set a Uri.
         *
         * \satisfy [SWS_REST_02179] Syntax Requirement for ara::rest::RequestHeader::SetUri.
         */
        void SetUri(const Uri &uri);

        /**
         * \brief   Returns the current message status code.
         *
         * \satisfy [SWS_REST_02507] Syntax Requirement for ara::rest::RequestHeader::GetStatus.
         */
        StatusCode GetStatus() const;

        /**
         * \brief   Sets a message status code.
         *
         * \satisfy [SWS_REST_02508] Syntax Requirement for ara::rest::RequestHeader::SetStatus.
         */
        void SetStatus(StatusCode code) noexcept;

    private:
        RequestMethod method_;
        Uri uri_;
        StatusCode status_;
    };

    class ReplyHeader
    {
    public:
        /**
         * \brief   Default-constructs a RequestHeader.
         */
        ReplyHeader() = default;

        /**
         * \brief
         */
        ReplyHeader(Uri uri, int status);
        ReplyHeader(Uri uri, StatusCode status);

    public:
        /**
         * \brief   Returns the current message status code.
         *
         * \satisfy [SWS_REST_02165] Syntax Requirement for ara::rest::ReplyHeader::GetStatus.
         */
        StatusCode GetStatus() const;

        /**
         * \brief   Sets a message status code.
         *
         * \satisfy [SWS_REST_02166] Syntax Requirement for ara::rest::ReplyHeader::SetStatus.
         */
        void SetStatus(StatusCode code) noexcept;

        /**
         * \brief   Returns a Uri.
         *
         * \satisfy [SWS_REST_02167] Syntax Requirement for ara::rest::ReplyHeader::GetUri.
         */
        const Uri &GetUri() const;

        /**
         * \brief   Allows to set a Uri.
         *
         * \satisfy [SWS_REST_02168] Syntax Requirement for ara::rest::ReplyHeader::SetUri.
         */
        void SetUri(const Uri &uri);

    private:
        Uri uri_;
        StatusCode status_;
    };

}
}

#endif //REST_HEADER_H