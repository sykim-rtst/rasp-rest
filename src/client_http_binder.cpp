#include "../include/internal/ara/rest/client_http_binder.h"
#include <sstream>
#include <iostream>

#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"

namespace ara
{
namespace rest
{

    Task<void> ClientHttpBinder::Start()
    {
        std::promise<void> sessionPrepare;
        auto result = sessionPrepare.get_future();

        try
        {
            session_ = std::make_unique<HTTPClientSession>();
            sessionPrepare.set_value();
        }
        catch (const std::bad_alloc& e)
        {
            sessionPrepare.set_exception(std::current_exception());
        }

        return result;
    }

    Task<void> ClientHttpBinder::Stop(ShutdownPolicy policy)
    {
        return std::async(std::launch::deferred, [this](){ session_->reset(); });
    }

    Task<Pointer<Reply>> ClientHttpBinder::Send(const Request &request)
    {
        return std::async(std::launch::async, &ClientHttpBinder::DoSend, this, std::ref(request));
    }

    ErrorCode ClientHttpBinder::GetError() const
    {
        return ara::rest::ErrorCode();
    }

    void ClientHttpBinder::ObserveError(const Function<void(std::__1::error_code)> &handler)
    {

    }

    Pointer<Reply> ClientHttpBinder::DoSend(const Request &request)
    {
        HTTPRequest pocoRequest(HTTPRequest::HTTP_1_1);
        ConvertRequest(request, pocoRequest);

        auto body = Copy(request.GetObject())->Serialize();

        pocoRequest.setContentType("application/json");
        pocoRequest.setContentLength(body.length());

        std::ostream& requestPayload = session_->sendRequest(pocoRequest);
        requestPayload << body;
        requestPayload.flush();

        HTTPResponse pocoReply;
        std::istream& replyPayload = session_->receiveResponse(pocoReply);
        std::stringstream ss;
        Poco::StreamCopier::copyStream(replyPayload, ss);

        auto replyBody = ogm::Serializer::Deserialize(ss.str());
        Pointer<Reply> reply = std::make_unique<Reply>(request.GetUri(), pocoReply.getStatus(), replyBody);

        return reply;
    }

    bool ClientHttpBinder::ConvertRequest(const Request &from, HTTPRequest &to)
    {
        bool result = false;

        switch (from.GetMethod())
        {
            case RequestMethod::kGet:       to.setMethod(HTTPRequest::HTTP_GET);     break;
            case RequestMethod::kPost:      to.setMethod(HTTPRequest::HTTP_POST);    break;
            case RequestMethod::kPut:       to.setMethod(HTTPRequest::HTTP_PUT);     break;
            case RequestMethod::kDelete:    to.setMethod(HTTPRequest::HTTP_DELETE);  break;
            case RequestMethod::kOptions:   to.setMethod(HTTPRequest::HTTP_OPTIONS); break;
            case RequestMethod::kHead:      to.setMethod(HTTPRequest::HTTP_HEAD);    break;
        }

        to.setHost(String(from.GetUri().GetHost()), static_cast<Poco::UInt16>(from.GetUri().GetPort()));

        String uri = "";
        std::for_each(from.GetUri().GetPath().GetSegments().Begin(), from.GetUri().GetPath().GetSegments().End(),
                      [&uri](const Uri::Path::Segment &seg)
                      {
                          uri += "/" + seg.Get();
                      });
        to.setURI(uri);

        session_->setHost(from.GetUri().GetHost());
        session_->setPort(static_cast<Poco::UInt16>(from.GetUri().GetPort()));

        return result;
    }
}
}
