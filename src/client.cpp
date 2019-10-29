#include <ara/rest/client.h>
#include "../include/internal/ara/rest/client_http_binder.h"

namespace ara
{
namespace rest
{

    /**
     * ara::rest::Client Constructors
     */
    Client::Client(const StringView &instanceId)
    {
        /**
         * @TODO Initialize ClientInterface
         */
        binding_ = std::make_unique<ClientHttpBinder>();
        binding_->Start();
    }

    /**
     * ara::rest::Client Member Functions
     */
    Task<void> Client::Stop(ShutdownPolicy policy)
    {
        return binding_->Stop(policy);
    }

    Task<Pointer<Reply>> Client::Send(const Request &request)
    {
        return binding_->Send(request);
    }

    Task<Event>
    Client::Subscribe(const Uri &uri, EventPolicy policy, const Function<NotificationHandlerType> &notify,
                      const Function<SubscriptionStateHandlerType > &state)
    {
        std::promise<Event> temp;
        return temp.get_future();

        //return binding_->Subscribe(uri, policy, notify, state);
    }

    ErrorCode Client::GetError() const
    {
        return binding_->GetError();
    }

    void Client::ObserveError(const Function<void(ErrorCode)> &handler)
    {
        binding_->ObserveError(handler);
    }

    /**
     * ara::rest::Request Constructors
     */
    rest::Request::Request(RequestMethod method, const Uri &uri)
            : header_(RequestHeader(method, uri))
    {

    }

    rest::Request::Request(RequestMethod method, Uri &&uri)
            : header_(RequestHeader(method, std::move(uri)))
    {

    }

    rest::Request::Request(RequestMethod method, const Uri &uri, const std::unique_ptr<ogm::Object> &payload)
            : header_(RequestHeader(method, uri)), payload_(ogm::Copy(payload))
    {

    }

    rest::Request::Request(RequestMethod method, const Uri &uri, std::unique_ptr<ogm::Object> &&payload)
            : header_(RequestHeader(method, uri)), payload_(std::move(payload))
    {

    }

    rest::Request::Request(RequestMethod method, Uri &&uri, const std::unique_ptr<ogm::Object> &payload)
            : header_(RequestHeader(method, std::move(uri))), payload_(ogm::Copy(payload))
    {

    }

    rest::Request::Request(RequestMethod method, Uri &&uri, std::unique_ptr<ogm::Object> &&payload)
            : header_(RequestHeader(method, std::move(uri))), payload_(std::move(payload))
    {

    }

    rest::Request::Request(RequestMethod method, const Uri &uri, std::unique_ptr<std::string> &&payload)
            : header_(RequestHeader(method, uri))
    {

    }

    /**
     * ara::rest::Request Member Functions
     */

    const RequestHeader &Request::GetHeader() const
    {
        return header_;
    }

    const Uri &Request::GetUri() const
    {
        return header_.GetUri();
    }

    RequestMethod Request::GetMethod() const
    {
        return header_.GetMethod();
    }

    const ogm::Object &Request::GetObject() const
    {
        return *payload_;
    }

    /**
     * ara::rest::Reply Constructors
     */
    Reply::Reply(const Uri &uri, StatusCode status)
            : header_(uri, status)
    {

    }

    Reply::Reply(const Uri &uri, StatusCode status, const Pointer<ara::rest::ogm::Object> &payload)
            : header_(uri, status), payload_(ogm::Copy(payload))
    {

    }

    Reply::Reply(const Uri &uri, StatusCode status, Pointer<ara::rest::ogm::Object> &&payload)
            : header_(uri, status), payload_(std::move(payload))
    {

    }

    /**
     * ara::rest::Reply Member Functions
     */
    ReplyHeader const &Reply::GetHeader() const
    {
        return header_;
    }

    ogm::Object const &Reply::GetObject() const
    {
        return *payload_;
    }

    Pointer<ogm::Object> &Reply::ReleaseObject()
    {
        return payload_;
    }

    Pointer<String> Reply::ReleaseBinary()
    {
        String binary = payload_->Serialize();
        return std::make_unique<String>(binary);
    }

    /**
     * ara::rest::Event Member Functions
     */
    std::future<bool> Event::Unsubscribe()
    {
        subscription_state_ = SubscriptionState::kCanceled;

        return std::future<bool>();
    }

    std::future<bool> Event::Resubscribe()
    {
        subscription_state_ = SubscriptionState::kResubscribe;

        return std::future<bool>();
    }

    const Uri &Event::GetUri() const
    {
        return uri_;
    }

    SubscriptionState Event::GetSubscriptionState() const
    {
        return subscription_state_;
    }

}
}