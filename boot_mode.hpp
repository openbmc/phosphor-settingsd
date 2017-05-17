#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Boot/Mode/server.hpp"

namespace phosphor
{
namespace settings
{
namespace boot
{

using ModeIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Boot::server::Mode>;

/** @class Mode
 *  @brief Boot Mode setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Boot.Mode interface.
 */
class Mode : public ModeIfaces
{
    public:
        Mode() = delete;
        Mode(const Mode&) = delete;
        Mode& operator=(const Mode&) = delete;
        Mode(Mode&&) = delete;
        Mode& operator=(Mode&&) = delete;
        virtual ~Mode() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Mode(sdbusplus::bus::bus& bus,
             const char* path):
            ModeIfaces(bus, path, true)
        {
        }
};

} // namespace boot
} // namespace settings
} // namespace phosphor
