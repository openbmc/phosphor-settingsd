#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Time/Owner/server.hpp"

namespace phosphor
{
namespace settings
{
namespace time
{

using OwnerIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Time::server::Owner>;

/** @class Owner
 *  @brief Time Owner setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Time.Owner interface.
 */
class Owner : public OwnerIfaces
{
    public:
        Owner() = delete;
        Owner(const Owner&) = delete;
        Owner& operator=(const Owner&) = delete;
        Owner(Owner&&) = delete;
        Owner& operator=(Owner&&) = delete;
        virtual ~Owner() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Owner(sdbusplus::bus::bus& bus,
              const char* path):
            OwnerIfaces(bus, path, true)
        {
        }
};

} // namespace time
} // namespace settings
} // namespace phosphor
