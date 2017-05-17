#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Security/RestrictionMode/server.hpp"

namespace phosphor
{
namespace settings
{
namespace security
{

using RestrictionModeIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::
    Security::server::RestrictionMode>;

/** @class RestrictionMode
 *  @brief RestrictionMode setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Security.RestrictionMode interface.
 */
class RestrictionMode : public RestrictionModeIfaces
{
    public:
        RestrictionMode() = delete;
        RestrictionMode(const RestrictionMode&) = delete;
        RestrictionMode& operator=(const RestrictionMode&) = delete;
        RestrictionMode(RestrictionMode&&) = delete;
        RestrictionMode& operator=(RestrictionMode&&) = delete;
        virtual ~RestrictionMode() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        RestrictionMode(sdbusplus::bus::bus& bus,
                        const char* path):
            RestrictionModeIfaces(bus, path, true)
        {
        }
};

} // namespace security
} // namespace settings
} // namespace phosphor
