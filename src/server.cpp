#include <ara/rest/server.h>
#include "../include/internal/ara/rest/server_http_binder.h"

namespace ara
{
namespace rest
{

    Server::Server(const StringView &instanceId, const Function<Server::RequestHandlerType> &handler)
    {
        bindings_.push_back(std::make_unique<ServerHttpBinder>(handler));
    }

    Task<void> Server::Start(StartupPolicy policy)
    {
        return std::async(std::launch::async, [this, &policy]() {
            std::for_each(bindings_.begin(), bindings_.end(), [&policy](const Pointer<ServerProtocolBinder>& binder) {
                binder->Start(policy);
            });
        });
    }

    Task<void> Server::Stop(ShutdownPolicy policy)
    {
        return std::async(std::launch::async, [this, &policy]() {
            std::for_each(bindings_.begin(), bindings_.end(), [&policy](const Pointer<ServerProtocolBinder>& binder) {
                binder->Stop(policy);
            });
        });
    }

    void Server::ObserveSubscriptions(const Function<Server::SubscriptionHandlerType> &subscriptionHandler,
                                      const Function<Server::SubscriptionStateHandlerType> &subscriptionStateHandler)
    {

    }

    ErrorCode Server::GetError() const
    {
        return ara::rest::ErrorCode();
    }

    void Server::ObserveError(const Function<void(ErrorCode)> &handler)
    {

    }

    /**
     * ara::rest::ServerRequest Constructors
     */
    ServerRequest::ServerRequest(RequestMethod method, const Uri &uri, const Pointer <ogm::Object> &payload)
            : header_(method, uri), payload_(ogm::Copy(payload))
    {

    }

    /**
     * ara::rest::ServerRequest Member Functions
     */
    const RequestHeader &ServerRequest::GetHeader() const
    {
        return header_;
    }

    const ogm::Object &ServerRequest::GetObject() const
    {
        return *payload_;
    }

    /**
     * ara::rest::ServerReply Constructors
     */
    ServerReply::ServerReply(const Uri &uri, StatusCode status, const Pointer<ogm::Object> &payload)
            : header_(uri, status), payload_(ogm::Copy(payload))
    {

    }

    /**
     * ara::rest::ServerReply Member Functions
     */
    const ReplyHeader & ServerReply::GetHeader() const
    {
        return header_;
    }

    StatusCode ServerReply::GetStatus() const
    {
        return header_.GetStatus();
    }

    void ServerReply::SetStatus(StatusCode code) noexcept
    {
        header_.SetStatus(code);
    }

    /**
     * ara::rest::ServerEvent Member Functions
     */
    Task<void> ServerEvent::Notify(const Pointer<ogm::Object> &data)
    {
        return Task<void>();
    }

    Task<void> ServerEvent::Notify()
    {
        return Task<void>();
    }

    void ServerEvent::SetSubscriptionState(const SubscriptionState state)
    {
        subscription_state_ = state;
    }

    SubscriptionState ServerEvent::GetSubscriptionState() const
    {
        return subscription_state_;
    }

    const Uri &ServerEvent::GetUri() const
    {
        return uri_;
    }

    void ServerEvent::SendError(const unsigned int errorCode, const StringView &errorMessage)
    {

    }

}
}