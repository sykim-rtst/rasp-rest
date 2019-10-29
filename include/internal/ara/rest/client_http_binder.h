#ifndef REST_CLIENT_HTTP_BINDER_H
#define REST_CLIENT_HTTP_BINDER_H

#include <ara/rest/client.h>

#include "Poco/Net/HTTPClientSession.h"

using namespace Poco::Net;

namespace ara
{
namespace rest
{

    class ClientHttpBinder : public ClientProtocolBinder
    {
    public:
        ClientHttpBinder() = default;

    public:
        Task<void> Start() override;

        Task<void> Stop(ShutdownPolicy policy) override;

        Task<Pointer<Reply>> Send(const Request &request) override;

        /*
        Task<Event>
        Subscribe(const Uri &uri,
                EventPolicy policy,
                const Function<Client::NotificationHandlerType> &notify,
                const Function<Client::SubscriptionStateHandlerType> &state) override;
        */
        ErrorCode GetError() const override;

        void ObserveError(const Function<void(std::__1::error_code)> &handler) override;

    private:
        Pointer<Reply> DoSend(const Request &request);

        bool ConvertRequest(const Request &from, HTTPRequest &to);

    private:
        Pointer<HTTPClientSession> session_;
    };

}
}

#endif //REST_CLIENT_HTTP_BINDER_H
