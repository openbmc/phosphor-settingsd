#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Time/NTP/server.hpp"

namespace phosphor
{
namespace settings
{
namespace time
{

using NTPIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Time::server::NTP>;

/** @class NTP
 *  @brief DHCPProvidedNTP setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Time.NTP interface.
 */
class NTP : public NTPIfaces
{
    public:
        NTP() = delete;
        NTP(const NTP&) = delete;
        NTP& operator=(const NTP&) = delete;
        NTP(NTP&&) = delete;
        NTP& operator=(NTP&&) = delete;
        virtual ~NTP() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        NTP(sdbusplus::bus::bus& bus,
            const char* path):
            NTPIfaces(bus, path, true)
        {
        }
};

} // namespace time
} // namespace settings
} // namespace phosphor
