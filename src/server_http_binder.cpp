#include "../include/internal/ara/rest/server_http_binder.h"

#include <iostream>

namespace ara
{
namespace rest
{
    ServerHttpBinder::ServerHttpBinder(Function<Server::RequestHandlerType> handler)
            : server_(std::make_unique<HTTPServer>(new MyRequestHandlerFactory(handler), ServerSocket(9090), new HTTPServerParams)), isRunning_(false)
    {

    }

    Task<void> ServerHttpBinder::Start(StartupPolicy policy)
    {
        return std::async(DetermineAsyncLaunchPolicy(policy), [this]()
        {
            server_->start();

            isRunning_ = true;

            std::unique_lock<std::mutex> lock(requestWaitMutex_);
            requestWaitCv_.wait(lock, [&] { return !isRunning_; });

            lock.unlock();
        });
    }

    Task<void> ServerHttpBinder::Stop(ShutdownPolicy policy)
    {
        bool abortCurrent = (policy == ShutdownPolicy::kForced);
        return std::async([this, &abortCurrent]() { server_->stopAll(abortCurrent); isRunning_ = false;});
    }

    void ServerHttpBinder::ObserveSubscriptions(
            const Function<Server::SubscriptionHandlerType> &subscriptionHandler,
            const Function<Server::SubscriptionStateHandlerType> &subscriptionStateHandler)
    {

    }

    ErrorCode ServerHttpBinder::GetError() const
    {
        return ara::rest::ErrorCode();
    }

    void ServerHttpBinder::ObserveError(const Function<void(std::__1::error_code)> &handler)
    {

    }

    std::launch ServerHttpBinder::DetermineAsyncLaunchPolicy(StartupPolicy policy)
    {
        std::launch launchType = std::launch::any;
        if (policy == StartupPolicy::kDetached)
        {
            launchType = std::launch::async;
        }
        else if (policy == StartupPolicy::kAttached)
        {
            launchType = std::launch::deferred;
        }

        return launchType;
    }

    void ServerHttpRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        auto uri = Uri::Builder("http://" + request.getHost() + request.getURI()).ToUri();
        handler_(ServerHttpRequest::MakeFrom(&request, uri), ServerHttpReply::MakeFrom(&response, uri));
    }

    Task<void> ServerHttpReply::Send(const Pointer<ara::rest::ogm::Object> &data)
    {
        return Send(data->Serialize());
    }

    Task<void> ServerHttpReply::Send(Pointer<ara::rest::ogm::Object> &&data)
    {
        String serializedData = data->Serialize();
        return Send(serializedData);
    }

    Task<void> ServerHttpReply::Send(const StringView &data)
    {
        return std::async([this, &data]() {
            pocoReply_->setStatus(StatusCode::ToString(GetStatus()));
            pocoReply_->setContentType("application/json");
            pocoReply_->setContentLength(data.size());

            std::ostream& out = pocoReply_->send();
            out << data;
            out.flush();
        });
    }

    Task<void> ServerHttpReply::Redirect(const Uri &uri)
    {
        return std::async([this, &uri]() {
            pocoReply_->redirect("" /** Stringify( Uri ) */);
        });
    }
}
}