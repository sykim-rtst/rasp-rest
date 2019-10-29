#ifndef REST_SERVER_HTTP_BINDER_H
#define REST_SERVER_HTTP_BINDER_H

#include <ara/rest/server.h>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerRequestImpl.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

using namespace Poco::Net;

namespace ara
{
namespace rest
{

    class ServerHttpBinder : public ServerProtocolBinder
    {
    public:
        ServerHttpBinder(Function<Server::RequestHandlerType> handler);

    public:
        Task<void> Start(StartupPolicy policy) override;

        Task<void> Stop(ShutdownPolicy policy) override;

        void ObserveSubscriptions(const Function<Server::SubscriptionHandlerType> &subscriptionHandler,
                                  const Function<Server::SubscriptionStateHandlerType> &subscriptionStateHandler) override;

        ErrorCode GetError() const override;

        void ObserveError(const Function<void(ErrorCode)> &handler) override;

    private:
        Pointer<HTTPServer> server_;

        std::mutex requestWaitMutex_;
        std::condition_variable requestWaitCv_;

        bool isRunning_;

        std::launch DetermineAsyncLaunchPolicy(StartupPolicy policy);
    };

    class ServerHttpRequestHandler : public HTTPRequestHandler
    {
    public:
        ServerHttpRequestHandler(Function<Server::RequestHandlerType> handler) : handler_(handler) {};

        void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) override;

    private:
        Function<Server::RequestHandlerType> handler_;
    };

    class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
    {
    public:
        MyRequestHandlerFactory(Function<Server::RequestHandlerType> handler) : handler_(handler) {};

        virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &) override
        {
            return new ServerHttpRequestHandler(handler_);
        }

    private:
        Function<Server::RequestHandlerType> handler_;
    };

    class ServerHttpRequest : public ServerRequest
    {
    public:
        static ServerHttpRequest &MakeFrom(HTTPServerRequest *request, const Uri &uri)
        {
            static ServerHttpRequest serverRequest(RequestMethod::kGet, uri, ogm::Object::Make(), request);
            return serverRequest;
        }

    private:
        Pointer<HTTPServerRequest> pocoRequest_;

        ServerHttpRequest(RequestMethod method, const Uri &uri, const Pointer<ogm::Object> &payload, HTTPServerRequest *request)
                : ServerRequest(method, uri, payload), pocoRequest_(request)
        {};
    };

    class ServerHttpReply : public ServerReply
    {
    public:
        static ServerHttpReply &MakeFrom(HTTPServerResponse *reply, const Uri &uri)
        {
            static ServerHttpReply serverReply(Uri(), 0, ogm::Object::Make(), reply);
            return serverReply;
        }

        Task<void> Send(const Pointer<ara::rest::ogm::Object> &data) override;
        Task<void> Send(Pointer<ara::rest::ogm::Object> &&data) override;
        Task<void> Send(const StringView &data) override;
        Task<void> Redirect(const Uri &uri) override;

    private:
        Pointer<HTTPServerResponse> pocoReply_;

        ServerHttpReply(const Uri &uri, int status, const Pointer<ogm::Object> &payload, HTTPServerResponse *reply)
                : ServerReply(uri, status, payload), pocoReply_(reply)
        {};
    };

}
}

#endif //REST_SERVER_HTTP_BINDER_H
