#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Boot/Source/server.hpp"

namespace phosphor
{
namespace settings
{
namespace boot
{

using SourceIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Boot::server::Source>;

/** @class Source
 *  @brief Boot Source setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Boot.Source interface.
 */
class Source : public SourceIfaces
{
    public:
        Source() = delete;
        Source(const Source&) = delete;
        Source& operator=(const Source&) = delete;
        Source(Source&&) = delete;
        Source& operator=(Source&&) = delete;
        virtual ~Source() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Source(sdbusplus::bus::bus& bus,
               const char* path):
            SourceIfaces(bus, path, true)
        {
        }
};

} // namespace boot
} // namespace settings
} // namespace phosphor
