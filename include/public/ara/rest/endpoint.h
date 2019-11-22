#ifndef REST_ENDPOINT_H
#define REST_ENDPOINT_H

#include <cstdint>

namespace ara
{
namespace rest
{
    /**
     * \brief   Specifies a set possible API access methods.
     */
    enum class RequestMethod : std::uint32_t
    {
        kGet        = 1 << 0,
        kPost       = 1 << 1,
        kPut        = 1 << 2,
        kDelete     = 1 << 3,
        kOptions    = 1 << 4,
        kHead       = 1 << 5
    };

    /**
     * \brief   Denotes the state of the subscription relation represented by an Event.
     */
    enum class SubscriptionState
    {
        kSubscribed,
        kCanceled,
        kResubscribe,
        kInvalid
    };

    /**
     * \brief   Mode of operation for event subscriptions.
     */
    enum class EventPolicy : std::uint32_t
    {
        kTriggered,
        kPeriodic
    };

    /**
     * \brief   Specifies shutdown behavior of endpoints.
     */
    enum class ShutdownPolicy : std::uint32_t
    {
        kForced,
        kGraceful
    };

    /**
     * \brief   Specifies whether a server will detach itself from its owning context.
     *
     * \satisfy [SWS_REST_01510] An implementation shall provide an enumeration ara::rest::StartupPolicy
     */
    enum class StartupPolicy : std::uint32_t
    {
        kDetached,
        kAttached
    };

}
}

#endif //REST_ENDPOINT_H