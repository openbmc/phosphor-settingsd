// WARNING: Generated header. Do not edit!
#pragma once

#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>
#include <utility>
#include <experimental/filesystem>
#include "config.h"

#include "xyz/openbmc_project/Control/Boot/Mode/server.hpp"


namespace phosphor
{
namespace settings
{

namespace fs = std::experimental::filesystem;

using namespace sdbusplus::xyz::openbmc_project::Control::Boot::server;

namespace xyz
{
namespace openbmc_project
{
namespace Control
{
namespace Boot
{
namespace Mode
{

using Base = sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

    decltype(std::declval<Base>().bootMode()) bootMode(decltype(std::declval<Base>().bootMode()) value) override
    {
        auto result = Base::bootMode();
        if (value != result)
        {
            fs::path p(SETTINGS_PERSIST_PATH);
            p /= path;
            fs::create_directories(p.parent_path());
            std::ofstream os(p.c_str(), std::ios::binary);
            cereal::JSONOutputArchive oarchive(os);
            result = Base::bootMode(value);
            oarchive(*this);
        }
        return result;
    }
    using Base::bootMode;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.bootMode());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.bootMode()) BootMode{};
    a(BootMode);
    setting.bootMode(BootMode);
}

} // namespace Mode
} // namespace Boot
} // namespace Control
} // namespace openbmc_project
} // namespace xyz

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
            fs::path path{};
            settings =
                std::make_tuple(
                    std::make_unique<xyz::openbmc_project::Control::Boot::Mode::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/boot_mode"),
                    std::make_unique<xyz::openbmc_project::Control::Boot::Mode::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host1/boot_mode"));

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/boot_mode";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<0>(settings));
            }
            else
            {
                std::get<0>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Safe);
            }
            std::get<0>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host1/boot_mode";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<1>(settings));
            }
            else
            {
                std::get<1>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Regular);
            }
            std::get<1>(settings)->emit_object_added();

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Mode::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Mode::Impl>> settings;
};

} // namespace settings
} // namespace phosphor
