// WARNING: Generated header. Do not edit!

#pragma once

#include "xyz/openbmc_project/Settings/Boot/Mode/server.hpp"
#include "xyz/openbmc_project/Settings/Boot/Mode/server.hpp"

using namespace sdbusplus::xyz::openbmc_project::Settings::Boot::server;
using namespace sdbusplus::xyz::openbmc_project::Settings::Boot::server;

namespace phosphor
{
namespace settings
{

/** @class Manager
 *
 *  @brief Compose settings objects and put them on the bus.
 */
class Manager
{
    public:
        Manager() = delete;
        Manager(const Manager&) = delete;
        Manager& operator=(const Manager&) = delete;
        Manager(Manager&&) = delete;
        Manager& operator=(Manager&&) = delete;
        virtual ~Manager() = default;

        /** @brief Constructor to put settings objects on to the bus.
         *  @param[in] bus - Bus to attach to.
         */
        Manager(sdbusplus::bus::bus& bus)
        {
            settings =
                std::make_tuple(
                    std::make_unique<sdbusplus::xyz::openbmc_project::Settings::Boot::server::Mode>(
                        bus,
                        "/xyz/openbmc_project/settings/host0/boot_mode"),
                    std::make_unique<sdbusplus::xyz::openbmc_project::Settings::Boot::server::Mode>(
                        bus,
                        "/xyz/openbmc_project/settings/host1/boot_mode"));

            std::get<0>(settings)->
                setPropertyByName("BootMode", Mode::Modes::Safe);
            bus.emit_object_added("/xyz/openbmc_project/settings/host0/boot_mode");

            std::get<1>(settings)->
                setPropertyByName("BootMode", Mode::Modes::Regular);
            bus.emit_object_added("/xyz/openbmc_project/settings/host1/boot_mode");

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<sdbusplus::xyz::openbmc_project::Settings::Boot::server::Mode>,
            std::unique_ptr<sdbusplus::xyz::openbmc_project::Settings::Boot::server::Mode>> settings;
};

} // namespace settings
} // namespace phosphor
