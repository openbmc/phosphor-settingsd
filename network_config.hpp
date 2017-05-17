#pragma once

#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include "xyz/openbmc_project/Settings/Network/Config/server.hpp"

namespace phosphor
{
namespace settings
{
namespace network
{

using ConfigIfaces = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Settings::Network::server::Config>;

/** @class Config
 *  @brief Network Config setting implementation
 *  @details A concrete implementation for the
 *  xyz.openbmc_project.Setting.Network.Config interface.
 */
class Config : public ConfigIfaces
{
    public:
        Config() = delete;
        Config(const Config&) = delete;
        Config& operator=(const Config&) = delete;
        Config(Config&&) = delete;
        Config& operator=(Config&&) = delete;
        virtual ~Config() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Config(sdbusplus::bus::bus& bus,
               const char* path):
            ConfigIfaces(bus, path, true)
        {
        }
};

} // namespace network
} // namespace settings
} // namespace phosphor
