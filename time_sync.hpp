#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Time/Synchronization/server.hpp"

namespace phosphor
{
namespace settings
{
namespace time
{

using SynchronizationIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Time::server::Synchronization>;

/** @class Synchronization
 *  @brief Time Synchronization setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Time.Synchronization interface.
 */
class Synchronization : public SynchronizationIfaces
{
    public:
        Synchronization() = delete;
        Synchronization(const Synchronization&) = delete;
        Synchronization& operator=(const Synchronization&) = delete;
        Synchronization(Synchronization&&) = delete;
        Synchronization& operator=(Synchronization&&) = delete;
        virtual ~Synchronization() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Synchronization(sdbusplus::bus::bus& bus,
                        const char* path):
            SynchronizationIfaces(bus, path, true)
        {
        }
};

} // namespace time
} // namespace settings
} // namespace phosphor
