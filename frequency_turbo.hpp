#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Frequency/Turbo/server.hpp"

namespace phosphor
{
namespace settings
{
namespace frequency
{

using TurboIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Frequency::server::Turbo>;

/** @class Turbo
 *  @brief Turbo Enabled setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Frequency.Turbo interface.
 */
class Turbo : public TurboIfaces
{
    public:
        Turbo() = delete;
        Turbo(const Turbo&) = delete;
        Turbo& operator=(const Turbo&) = delete;
        Turbo(Turbo&&) = delete;
        Turbo& operator=(Turbo&&) = delete;
        virtual ~Turbo() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Turbo(sdbusplus::bus::bus& bus,
              const char* path):
            TurboIfaces(bus, path, true)
        {
        }
};

} // namespace frequency
} // namespace settings
} // namespace phosphor
