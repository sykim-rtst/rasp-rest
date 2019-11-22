#ifndef REST_CLIENT_H
#define REST_CLIENT_H

#include <ara/rest/endpoint.h>
#include <ara/rest/header.h>
#include <ara/rest/uri.h>
#include <ara/rest/support_type.h>
#include <ara/rest/ogm/object.h>

namespace ara
{
namespace rest
{

    class Request;
    class Reply;
    class Event;
    class ClientProtocolBinder

    class Client
    {
    public:
        /**
         * \brief   Denotes a callback function for notifications.
         *
         * \satisfy [SWS_REST_02007] Syntax Requirement for ara::rest::Client::NotificationHandlerType.
         */
        using NotificationHandlerType       = void(const ogm::Object &);

        /**
         * \brief   Denotes a callback to call if subscription status changes.
         *
         * \satisfy [SWS_REST_02007] Syntax Requirement for ara::rest::Client::SubscriptionStateHandlerType.
         */
        using SubscriptionStateHandlerType  = void(Event, SubscriptionState);

    public:
        /**
         * \brief   Client is non-copy-constructible.
         *
         * \satisfy [SWS_REST_01403] ara::rest::Client shall not be copyable.
         * \satisfy [SWS_REST_02010] Syntax Requirement for Constructor.
         */
        Client(const Client &) = delete;

        /**
         * \brief   Client is non-copy-assignable.
         *
         * \satisfy [SWS_REST_01403] ara::rest::Client shall not be copyable.
         * \satisfy [SWS_REST_02011] Syntax Requirement for Assignment Operator.
         */
        Client &operator=(const Client &) = delete;

        /**
         * \brief   Constructs a client.
         *
         * \satisfy [SWS_REST_01407] ara::rest::Client shall be provided with a unique identifier.
         * \satisfy [SWS_REST_01408] ara::rest::Client shall be ready for transmission to remote hosts if Constructor succeeded.
         * \satisfy [SWS_REST_02007] Syntax Requirement for Constructor.
         */
        Client(const StringView &instanceId);

    public:
        /**
         * \brief   Requests a client shutdown.
         *
         * \satisfy [SWS_REST_01409] ara::rest::Client shall be stopped via ara::rest::Client::Stop.
         * \satisfy [SWS_REST_01410] ara::rest::Client::Stop shall be thread-safe.
         * \satisfy [SWS_REST_01411] ara::rest::Client::Stop returns a Task which shall only complete once shutdown succeeded.
         * \satisfy [SWS_REST_02012] Syntax Requirement for ara::rest::Client::Stop.
         */
        Task<void> Stop(ShutdownPolicy policy);

        /**
         * \brief   Issues a request to a peer.
         *
         * \satisfy [SWS_REST_01412] ara::rest::Client::Send shall transmit an ara::rest::Request.
         * \satisfy [SWS_REST_02013] Syntax Requirement for ara::rest::Client::Send.
         */
        Task<Pointer<Reply>> Send(const Request &request);

        /**
         * \brief   Performs an event subscription.
         *
         * \satisfy [SWS_REST_01414] An implementation shall provide ara::rest::Client::Subscribe to create ara::rest::Event instances.
         *                           ara::rest::Client::Subscribe shall never block.
         * \satisfy [SWS_REST_01415] The URI passed to ara::rest::Client::Subscribe denotes an entity to subscribe to.
         * \satisfy [SWS_REST_01416] An implementation shall honor the event policy passed to ara::rest::Client::Subscribe.
         * \satisfy [SWS_REST_01417] An instance of ara::rest::Client::NotificationHandlerType shall be passed to ara::rest::Client::Subscribe.
         * \satisfy [SWS_REST_01418] An instance of ara::rest::Client::SubscriptionStateHandlerType may be passed to ara::rest::Client::Subscribe.
         * \satisfy [SWS_REST_02014] Syntax Requirement for ara::rest::Client::Subscribe.
         */
        Task<Event> Subscribe(const Uri &uri,
                              EventPolicy policy,
                              const Function<NotificationHandlerType> &notify,
                              const Function<SubscriptionStateHandlerType> &state = {});

        /**
         * \brief   Obtain client status.
         *
         * \satisfy [SWS_REST_01420] All errors not leaving a client in an undefined state shall be indicated via ara::rest::Client::GetError and ara::rest::Client::ObserveError.
         * \satisfy [SWS_REST_02015] Syntax Requirement for ara::rest::Client::GetError.
         */
        ErrorCode GetError() const;

        /**
         * \brief   Observe status changes.
         *
         * \satisfy [SWS_REST_01420] All errors not leaving a client in an undefined state shall be indicated via ara::rest::Client::GetError and ara::rest::Client::ObserveError.
         * \satisfy [SWS_REST_02012=6] Syntax Requirement for ara::rest::Client::ObserveError.
         */
        void ObserveError(const Function<void(ErrorCode)> &handler);

    private:
        Pointer<ClientProtocolBinder> binding_;
    };

    class ClientProtocolBinder
    {
    public:
        /**
         * \brief   Requests a client startup.
         */
        virtual Task<void> Start() = 0;

        /**
         * \brief   Requests a client shutdown.
         */
        virtual Task<void> Stop(ShutdownPolicy policy) = 0;

        /**
         * \brief   Issues a request to a peer.
         */
        virtual Task<Pointer<Reply>> Send(const Request &request) = 0;

        /**
         * \brief   Performs an event subscription.
         */
        /*
       virtual Task<Event> Subscribe(const Uri &uri,
                             EventPolicy policy,
                             const Function<Client::NotificationHandlerType> &notify,
                             const Function<Client::SubscriptionStateHandlerType> &state = {}) = 0;
        */
        /**
         * \brief   Obtain client status.
         */
        virtual ErrorCode GetError() const = 0;

        /**
         * \brief   Observe status changes.
         */
        virtual void ObserveError(const Function<void(ErrorCode)> &handler) = 0;

    public:
        virtual ~ClientProtocolBinder() = default;

    protected:
        ClientProtocolBinder() = default;

        friend Client;
    };

    class Request
    {
    public:
        /**
         * \brief   Non-copyable.
         *
         * \satisfy [SWS_REST_01421] ara::rest::Request shall be non-copyable.
         * \satisfy [SWS_REST_02181] Syntax Requirement for Constructor.
         */
        Request(const Request &) = delete;

        /**
         * \brief   Non-copy-assignable.
         *
         * \satisfy [SWS_REST_01421] ara::rest::Request shall be non-copyable.
         * \satisfy [SWS_REST_02182] Syntax Requirement for Assignment Operator.
         */
        Request &operator=(const Request &) = delete;

        //Request(Request&&) = default;
        //Request& operator=(Request&&) = default;

        /**
         * \brief   Constructs a Request.
         *
         * \satisfy [SWS_REST_02183] Syntax Requirement for Constructor.
         */
        Request(RequestMethod method, const Uri &uri);

        /**
         * \brief   Constructs a Request.
         *
         * \satisfy [SWS_REST_02184] Syntax Requirement for Constructor.
         */
        Request(RequestMethod method, Uri &&uri);

        /**
         * \brief   Constructs a Request.
         *
         * \satisfy [SWS_REST_02185] Syntax Requirement for Constructor.
         */
        Request(RequestMethod method, const Uri &uri, const Pointer<ogm::Object> &payload);

        /**
         * \brief   Constructs a Request.
         *
         * \satisfy [SWS_REST_02186] Syntax Requirement for Constructor.
         */
        Request(RequestMethod method, const Uri &uri, Pointer<ogm::Object> &&payload);

        /**
         * \brief   Constructs a Request.
         *
         * \satisfy [SWS_REST_021837] Syntax Requirement for Constructor.
         */
        Request(RequestMethod method, Uri &&uri, const Pointer<ogm::Object> &payload);

        /**
         * \brief   Constructs a Request.
         *
         * \satisfy [SWS_REST_02188] Syntax Requirement for Constructor.
         */
        Request(RequestMethod method, Uri &&uri, Pointer<ogm::Object> &&payload);

        /**
         * \brief   Constructs a Request.
         *
         * \satisfy [SWS_REST_02189] Syntax Requirement for Constructor.
         */
        Request(RequestMethod method, const Uri &uri, Pointer<String> &&payload);
    };

    class Reply
    {
    public:
        /**
         * \brief   Non-copyable.
         *
         * \satisfy [SWS_REST_01421] ara::rest::Reply shall be non-copyable.
         * \satisfy [SWS_REST_02170] Syntax Requirement for Constructor.
         */
        Reply(const Reply &) = delete;

        /**
         * \brief   Non-copy-assignable.
         *
         * \satisfy [SWS_REST_01421] ara::rest::Reply shall be non-copyable.
         * \satisfy [SWS_REST_02170] Syntax Requirement for Assignment Operator.
         */
        Reply &operator=(const Reply &) = delete;

        Reply(const Uri &uri, StatusCode status);
        Reply(const Uri &uri, StatusCode status, const Pointer<ogm::Object> &payload);
        Reply(const Uri &uri, StatusCode status, Pointer<ogm::Object> &&payload);

    public:
        /**
         * \brief   Obtains the message header.
         *
         * \satisfy [SWS_REST_02170] Syntax Requirement for ara::rest::Reply::GetHeader.
         */
        ReplyHeader const & GetHeader() const;

        /**
         * \brief   Obtains the reply message payload.
         *
         * \satisfy [SWS_REST_02171] Syntax Requirement for ara::rest::Reply::GetObject.
         */
        ogm::Object const& GetObject() const;

        /**
         * \brief   Obtains the reply message payload.
         *
         * \satisfy [SWS_REST_02172] Syntax Requirement for ara::rest::Reply::ReleaseObject.
         */
        Pointer<ogm::Object> &ReleaseObject();

        /**
         * \brief   Obtains the reply binary payload.
         *
         * \satisfy [SWS_REST_02173] Syntax Requirement for ara::rest::Reply::ReleaseBinary.
         */
        Pointer<String> ReleaseBinary();

    private:
        ReplyHeader header_;
        // Pointer<ogm::Object> payload_;
    };

    class Event
    {
    public:

        /**
         * \brief   Non-copyable.
         *
         * \satisfy [SWS_REST_02170] Syntax Requirement for Constructor.
         */
        Event(const Event &) = delete;

        /**
         * \brief   Non-copy-assignable.
         *
         * \satisfy [SWS_REST_02170] Syntax Requirement for Assignment Operator.
         */
        Event &operator=(const Event &) = delete;

    public:
        /**
         * \brief   Cancels an event subscription by issuing a cancelation request.
         *
         * \satisfy [SWS_REST_02170] Syntax Requirement for ara::rest::Event::Unsubscribe.
         */
        Task<bool> Unsubscribe();

        /**
         * \brief   Re-subscribes to an event.
         *
         * \satisfy [SWS_REST_02170] Syntax Requirement for ara::rest::Event::Resubscribe.
         */
        Task<bool> Resubscribe();

        /**
         * \brief   Returns the event Uri.
         *
         * \satisfy [SWS_REST_02170] Syntax Requirement for ara::rest::Event::GetUri.
         */
        const Uri & GetUri() const;

        /**
         * \brief   Returns the event Uri.
         *
         * \satisfy [SWS_REST_02170] Syntax Requirement for ara::rest::Event::GetSubscriptionState.
         */
        SubscriptionState GetSubscriptionState() const;

    private:
        Uri uri_;
        SubscriptionState subscription_state_;
    };

    /**
     * \brief   Tests events for equality.
     *
     * \satisfy [SWS_REST_02170] Syntax Requirement for Relational Operators.
     */
    inline bool operator==(const Event &a, const Event &b) noexcept
    {

    }

    /**
     * \brief   Tests events for inequality.
     *
     * \satisfy [SWS_REST_02170] Syntax Requirement for Relational Operators.
     */
    inline bool operator!=(const Event &a, const Event &b) noexcept
    {

    }

    /**
     * \brief   Tests events for their partial order Order criterion is implementation-defined.
     *
     * \satisfy [SWS_REST_02170] Syntax Requirement for Relational Operators.
     */
    inline bool operator<(const Event &a, const Event &b) noexcept
    {

    }

}
}