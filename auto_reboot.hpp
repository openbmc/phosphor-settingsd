#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Boot/RebootPolicy/server.hpp"

namespace phosphor
{
namespace settings
{
namespace boot
{

using RebootPolicyIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Boot::server::RebootPolicy>;

/** @class RebootPolicy
 *  @brief Auto Reboot setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Boot.RebootPolicy interface.
 */
class RebootPolicy : public RebootPolicyIfaces
{
    public:
        RebootPolicy() = delete;
        RebootPolicy(const RebootPolicy&) = delete;
        RebootPolicy& operator=(const RebootPolicy&) = delete;
        RebootPolicy(RebootPolicy&&) = delete;
        RebootPolicy& operator=(RebootPolicy&&) = delete;
        virtual ~RebootPolicy() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        RebootPolicy(sdbusplus::bus::bus& bus,
                     const char* path):
            RebootPolicyIfaces(bus, path, true)
        {
        }
};

} // namespace boot
} // namespace settings
} // namespace phosphor
