#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Power/RestorePolicy/server.hpp"

namespace phosphor
{
namespace settings
{
namespace power
{

using RestorePolicyIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Power::server::RestorePolicy>;

/** @class RestorePolicy
 *  @brief Power RestorePolicy setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Power.RestorePolicy interface.
 */
class RestorePolicy : public RestorePolicyIfaces
{
    public:
        RestorePolicy() = delete;
        RestorePolicy(const RestorePolicy&) = delete;
        RestorePolicy& operator=(const RestorePolicy&) = delete;
        RestorePolicy(RestorePolicy&&) = delete;
        RestorePolicy& operator=(RestorePolicy&&) = delete;
        virtual ~RestorePolicy() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        RestorePolicy(sdbusplus::bus::bus& bus,
                      const char* path):
            RestorePolicyIfaces(bus, path, true)
        {
        }
};

} // namespace power
} // namespace settings
} // namespace phosphor
