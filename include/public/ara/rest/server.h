//
// Created by yongjin.seo on 12/06/2019.
//

#ifndef REST_SERVER_H
#define REST_SERVER_H

#include <ara/rest/endpoint.h>
#include <ara/rest/header.h>
#include <ara/rest/uri.h>
#include <ara/rest/support_type.h>
#include <ara/rest/ogm/object.h>

namespace ara
{
namespace rest
{
    class ServerRequest;
    class ServerReply;
    class ServerEvent;
    class ServerProtocolBinder;

    /**
     * @unsatiafy   [SWS_REST_01501] ara::rest::Server maintains all resources related to communication with a peer.
     *              [SWS_REST_01502] An ara::rest::Server shall at least provide the interface
     *              [SWS_REST_01504] ara::rest::Server shall be able to handle multiple transport protocol bindings concurrently.
     *              [SWS_REST_01505] ara::rest::Server shall be able to handle multiple peers concurrently over potentially multiple transport protocols.
     *              [SWS_REST_01506] ara::rest::Server shall be able to operate according to its semantic requirements without employing multi-threading.
     *                               Consequently, a user shall be aware of the fact that invoking blocking functions such as ara::rest::Task<T>::wait() may degrade service quality.
     *              [SWS_REST_01507] It is implementation-defined whether ara::rest::Server is operating concurrently.
     *              [SWS_REST_01513] ara::rest::Server shall leave its instances in a well-defined state after shutdown such that a subsequent startup remains feasible.
     *              [SWS_REST_01518]
     *              [SWS_REST_01519]
     *              [SWS_REST_01522]
     */

    class Server
    {
    public:
        /**
         * \brief   Type of user-defined request handlers.
         *
         * \satisfy [SWS_REST_02239] Syntax Requirement for ara::rest::Server::RequestHandlerType
         */
        using RequestHandlerType            = void(const ServerRequest&, ServerReply&);

        /**
         * \brief   Denotes a subscription handler type.
         *
         * \satisfy [SWS_REST_02240] Syntax Requirement for ara::rest::Server::SubscriptionHandlerType.
         */
        using SubscriptionHandlerType       = void(ServerEvent);

        /**
         * \brief   Denotes a callback to call if subscription status changes.
         *
         * \satisfy [SWS_REST_02241] Syntax Requirement for ara::rest::Server::SubscriptionStateHandlerType.
         */
        using SubscriptionStateHandlerType  = void(ServerEvent&, SubscriptionState);

    public:
        /**
         * \brief   Server is non-copy-constructible.
         *
         * \satisfy [SWS_REST_01503] ara::rest::Server shall not be copyable.
         * \satisfy [SWS_REST_02242] Syntax Requirement for Constructor.
         */
        Server(const Server &) = delete;

        /**
         * \brief   Server is non-copy-assignable.
         *
         * \satisfy [SWS_REST_01503] ara::rest::Server shall not be copyable.
         * \satisfy [SWS_REST_02243] Syntax Requirement for Assignment Operator.
         */
        Server &operator=(const Server &) = delete;

        /**
         * \brief   Constructs a server.
         *
         * \satisfy [SWS_REST_01508] ara::rest::Server shall be provided with a unique identifier.
         * \satisfy [SWS_REST_01516] ara::rest::Server shall invoke the user-defined handler function.
         * \satisfy [SWS_REST_02244] Syntax Requirement for Constructor.
         */
        Server(const StringView &instanceId, const Function<RequestHandlerType> &handler);

        /**
         * \brief   Instruct a server to begin serving clients.
         *
         * \satisfy [SWS_REST_01509] ara::rest::Server shall be provided with a unique identifier.
         * \satisfy [SWS_REST_01511] ara::rest::Server::Start returns a Task which shall only complete once startup succeeded.
         * \satisfy [SWS_REST_02245] Syntax Requirement for ara::rest::Server::Start.
         */
        Task<void> Start(StartupPolicy policy = StartupPolicy::kDetached);

        /**
         * \brief   Instructs a server to stop serving clients.
         *
         * \satisfy [SWS_REST_01512] ara::rest::Server shall be stopped via ara::rest::Server::Stop.
         * \satisfy [SWS_REST_01514] ara::rest::Server::Stop shall be thread-safe.
         * \satisfy [SWS_REST_01515] ara::rest::Server::Stop returns a Task which shall only complete once shutdown succeeded.
         * \satisfy [SWS_REST_02246] Syntax Requirement for ara::rest::Server::Stop.
         */
        Task<void> Stop(ShutdownPolicy policy = ShutdownPolicy::kGraceful);

        /**
         * \brief   Registers a user-defined subscription handler.
         *
         * \satisfy [SWS_REST_01517] ara::rest::Server shall accept event subscriptions without user-intervention.
         *                           It shall inform the application of new subscriptions or subscription state changes via ara::rest::Server::ObserveSubscriptions.
         * \satisfy [SWS_REST_02247] Syntax Requirement for ara::rest::Server::ObserveSubscriptions.
         */
        void ObserveSubscriptions(
                const Function<SubscriptionHandlerType> &subscriptionHandler,
                const Function<SubscriptionStateHandlerType> &subscriptionStateHandler
        );

        /**
         * \brief   Obtain server status.
         *
         * \satisfy [SWS_REST_02248] Syntax Requirement for ara::rest::Server::GetError.
         */
        ErrorCode GetError() const;

        /**
         * \brief   Observe status changes.
         *
         * \satisfy [SWS_REST_02249] Syntax Requirement for ara::rest::Server::ObserveError.
         */
        void ObserveError(const Function<void(ErrorCode)> &handler);

    private:
        std::vector<Pointer<ServerProtocolBinder>> bindings_;
    };

    class ServerProtocolBinder
    {
    public:
        virtual ~ServerProtocolBinder() = default;

    public:
        /**
         * \brief   Instruct a server to begin serving clients.
         */
        virtual Task<void> Start(StartupPolicy policy = StartupPolicy::kDetached) = 0;

        /**
         * \brief   Instructs a server to stop serving clients.
         */
        virtual Task<void> Stop(ShutdownPolicy policy = ShutdownPolicy::kGraceful) = 0;

        /**
         * \brief   Registers a user-defined subscription handler.
         */
        virtual void ObserveSubscriptions(
                const Function<Server::SubscriptionHandlerType> &subscriptionHandler,
                const Function<Server::SubscriptionStateHandlerType> &subscriptionStateHandler
        ) = 0;

        /**
         * \brief   Obtain server status.
         */
        virtual ErrorCode GetError() const = 0;

        /**
         * \brief   Observe status changes.
         */
        virtual void ObserveError(const Function<void(ErrorCode)> &handler) = 0;
    };

    class ServerRequest
    {
    public:
        /**
         * \brief   Non-copyable.
         *
         * \satisfy [SWS_REST_02233] Syntax Requirement for Constructor.
         */
        ServerRequest(const ServerRequest &) = delete;

        /**
         * \brief   Non-copy-assignable.
         *
         * \satisfy [SWS_REST_02234] Syntax Requirement for Assignment Operator.
         */
        ServerRequest &operator=(const ServerRequest &) = delete;

        ServerRequest() = default;
        ServerRequest(RequestMethod method, const Uri &uri, const Pointer<ogm::Object> &payload);

    public:
        /**
         * \brief   Provides access to the message header.
         *
         * \satisfy [SWS_REST_02235] Syntax Requirement for ara::rest::ServerRequest::GetHeader.
         */
        RequestHeader const & GetHeader() const;

        /**
         * \brief   Obtains the request message payload.
         *
         * \satisfy [SWS_REST_02236] Syntax Requirement for ara::rest::ServerRequest::GetObject.
         */
        ogm::Object const& GetObject() const;

        /**
         * \brief   Obtains the reply message payload.
         *
         * \satisfy [SWS_REST_02237] Syntax Requirement for ara::rest::ServerRequest::ReleaseObject.
         */
        Task<Pointer<ogm::Object>> ReleaseObject();

        /**
         * \brief   Obtains the reply message payload.
         *
         * \satisfy [SWS_REST_02991] Syntax Requirement for ara::rest::ServerRequest::ReleaseBinary.
         */
        Task<Pointer<String>> ReleaseBinary();

    private:
        RequestHeader header_;
        Pointer<ogm::Object> payload_;
    };

    class ServerReply
    {
    public:
        /**
         * \brief   Non-copyable.
         *
         * \satisfy [SWS_REST_02226] Syntax Requirement for Constructor.
         */
        ServerReply(const ServerReply &) = delete;

        /**
         * \brief   Non-copy-assignable.
         *
         * \satisfy [SWS_REST_02227] Syntax Requirement for Assignment Operator.
         */
        ServerReply &operator=(const ServerReply &) = delete;

        ServerReply(const Uri &uri, StatusCode status, const Pointer<ogm::Object> &payload);

    public:
        /**
         * \brief   Provides access to the reply message header.
         *
         * \satisfy [SWS_REST_02228] Syntax Requirement for ara::rest::ServerReply::GetHeader.
         */
        const ReplyHeader & GetHeader() const;

        /**
         * \brief   Send a reply to the peer that has issued the request.
         *
         * \satisfy [SWS_REST_02229] Syntax Requirement for ara::rest::ServerReply::Send.
         */
        virtual Task<void> Send(const Pointer<ogm::Object> &data = {}) = 0;

        /**
         * \brief   Send a reply to the peer that has issued the request.
         *
         * \satisfy [SWS_REST_02230] Syntax Requirement for ara::rest::ServerReply::Send.
         */
        virtual Task<void> Send(Pointer<ogm::Object> &&data) = 0;

        /**
         * \brief   Send a reply with binary data to the peer that has issued the request.
         *
         * \satisfy [SWS_REST_02232] Syntax Requirement for ara::rest::ServerReply::Send.
         */
        virtual Task<void> Send(const StringView &data) = 0;

        /**
         * \brief   Issues a redirect command to the connected client.
         *
         * \satisfy [SWS_REST_02231] Syntax Requirement for ara::rest::ServerReply::Redirect.
         */
        virtual Task<void> Redirect(const Uri &uri) = 0;

    private:
        ReplyHeader header_;
        Pointer<ogm::Object> payload_;
    };

    class ServerEvent
    {
    public:
        /**
         * \brief   Non-copyable.
         *
         * \satisfy [SWS_REST_02216] Syntax Requirement for Constructor.
         */
        ServerEvent(const ServerEvent &) = delete;

        /**
         * \brief   Non-copy-assignable.
         *
         * \satisfy [SWS_REST_02217] Syntax Requirement for Assignment Operator.
         */
        ServerEvent &operator=(const ServerEvent &) = delete;

        /**
         * \brief   Issues a change notification to its corresponding Server.
         *
         * \satisfy [SWS_REST_01525] ara::rest::ServerEvent::Notify shall notify its corresponding ara::rest::Server instance of potential updates.
         * \satisfy [SWS_REST_02218] Syntax Requirement for ara::rest::ServerEvent::Notify.
         */
        Task<void> Notify(const Pointer<ogm::Object> &data);

        /**
         * \brief   Issues a change notification to its corresponding Server.
         *
         * \satisfy [SWS_REST_02889] Syntax Requirement for ara::rest::ServerEvent::Notify.
         */
        Task<void> Notify();

        /**
         * \brief   Set subscription state from server side.
         *
         * \satisfy [SWS_REST_01523] ara::rest::ServerEvent::SetSubscriptionState called with parameter ara::rest::SubscriptionState::kCanceled shall cancel the subscription.
         * \satisfy [SWS_REST_01524] Once ara::rest::ServerEvent::SetSubscriptionState with parameter ara::rest::SubscriptionState::kCanceled is called,
         *                           resubscription on the same object shall not be allowed.
         * \satisfy [SWS_REST_02219] Syntax Requirement for ara::rest::ServerEvent::SetSubscriptionState.
         */
        void SetSubscriptionState(const SubscriptionState state);

        /**
         * \brief   Denotes the current subscription state.
         *
         * \satisfy [SWS_REST_02220] Syntax Requirement for ara::rest::ServerEvent::GetSubscriptionState.
         */
        SubscriptionState GetSubscriptionState() const;

        /**
         * \brief   Denotes the current subscription state.
         *
         * \satisfy [SWS_REST_02221] Syntax Requirement for ara::rest::ServerEvent::GetUri.
         */
        const Uri & GetUri() const;

        /**
         * \brief   During the life time of an event an error can occur.
         *
         * \satisfy [SWS_REST_02805] Syntax Requirement for ara::rest::ServerEvent::SendError.
         */
        void SendError(const unsigned int errorCode, const StringView &errorMessage);

        /**
         * \brief   Tests events for equality.
         *
         * \satisfy [SWS_REST_02222] Syntax Requirement for Relational Operators.
         */
        friend bool operator==(const ServerEvent &a, const ServerEvent &b) noexcept;

        /**
         * \brief   Tests events for inequality.
         *
         * \satisfy [SWS_REST_02223] Syntax Requirement for Relational Operators.
         */
        friend bool operator!=(const ServerEvent &a, const ServerEvent &b) noexcept;

        /**
         * \brief   Tests events for their partial order Order criterion is implementation- defined.
         *
         * \satisfy [SWS_REST_02224] Syntax Requirement for Relational Operators.
         */
        friend bool operator<(const ServerEvent &a, const ServerEvent &b) noexcept;

    private:
        Uri uri_;
        SubscriptionState subscription_state_;
    };

}
}

#endif //REST_SERVER_H
