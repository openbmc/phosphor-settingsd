#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Power/Cap/server.hpp"

namespace phosphor
{
namespace settings
{
namespace power
{

using CapIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Power::server::Cap>;

/** @class Cap
 *  @brief Power Cap setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Power.Cap interface.
 */
class Cap : public CapIfaces
{
    public:
        Cap() = delete;
        Cap(const Cap&) = delete;
        Cap& operator=(const Cap&) = delete;
        Cap(Cap&&) = delete;
        Cap& operator=(Cap&&) = delete;
        virtual ~Cap() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Cap(sdbusplus::bus::bus& bus,
            const char* path):
            CapIfaces(bus, path, true)
        {
        }
};

} // namespace power
} // namespace settings
} // namespace phosphor
