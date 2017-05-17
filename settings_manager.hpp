// WARNING: Generated header. Do not edit!

#pragma once

#include <tuple>
#include <memory>
#include "boot_mode.hpp"
#include "network_config.hpp"
#include "settings_scope.hpp"
#include "auto_reboot.hpp"
#include "boot_source.hpp"
#include "frequency_turbo.hpp"
#include "power_cap.hpp"
#include "power_restore_policy.hpp"
#include "restriction_mode.hpp"
#include "time_ntp.hpp"
#include "time_owner.hpp"
#include "time_sync.hpp"

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
                    std::make_unique<network::Config>(
                        bus,
                        "/xyz/openbmc_project/settings/host0/network_config"),
                    std::make_unique<boot::Mode>(
                        bus,
                        "/xyz/openbmc_project/settings/host0/boot_mode"),
                    std::make_unique<Scope>(
                        bus,
                        "/xyz/openbmc_project/settings/host0/boot_mode_scope"),
                    std::make_unique<boot::Mode>(
                        bus,
                        "/xyz/openbmc_project/settings/host1/boot_mode"));

            std::get<0>(settings)->
                setPropertyByName("Prefix", 32);
            std::get<0>(settings)->
                setPropertyByName("IPAddress", "0.0.0.0");
            std::get<0>(settings)->emit_object_added();

            std::get<1>(settings)->
                setPropertyByName("BootMode", boot::Mode::Modes::Safe);
            std::get<1>(settings)->emit_object_added();

            std::get<2>(settings)->emit_object_added();

            std::get<3>(settings)->
                setPropertyByName("BootMode", boot::Mode::Modes::Regular);
            std::get<3>(settings)->emit_object_added();

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<network::Config>,
            std::unique_ptr<boot::Mode>,
            std::unique_ptr<Scope>,
            std::unique_ptr<boot::Mode>> settings;
};

} // namespace settings
} // namespace phosphor
