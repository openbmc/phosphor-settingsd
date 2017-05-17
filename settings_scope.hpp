#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Scope/server.hpp"

namespace phosphor
{
namespace settings
{

using ScopeIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::server::Scope>;

/** @class Scope
 *  @brief Scope setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Scope interface.
 */
class Scope : public ScopeIfaces
{
    public:
        Scope() = delete;
        Scope(const Scope&) = delete;
        Scope& operator=(const Scope&) = delete;
        Scope(Scope&&) = delete;
        Scope& operator=(Scope&&) = delete;
        virtual ~Scope() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Scope(sdbusplus::bus::bus& bus,
              const char* path):
            ScopeIfaces(bus, path, true)
        {
        }
};

} // namespace settings
} // namespace phosphor
