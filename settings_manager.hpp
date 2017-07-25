// WARNING: Generated header. Do not edit!
#pragma once

#include <cereal/archives/json.hpp>
#include <fstream>
#include <utility>
#include <experimental/filesystem>
#include <regex>
#include <phosphor-logging/elog.hpp>
#include <phosphor-logging/elog-errors.hpp>
#include <phosphor-logging/log.hpp>
#include "config.h"
#include <xyz/openbmc_project/Common/error.hpp>

#include "xyz/openbmc_project/Network/MACAddress/server.hpp"
#include "xyz/openbmc_project/Control/Power/Cap/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Mode/server.hpp"


namespace phosphor
{
namespace settings
{

namespace fs = std::experimental::filesystem;

using namespace sdbusplus::xyz::openbmc_project::Network::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Boot::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Power::server;

namespace xyz
{
namespace openbmc_project
{
namespace Network
{
namespace MACAddress
{

using Base = sdbusplus::xyz::openbmc_project::Network::server::MACAddress;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Network::server::MACAddress>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().mACAddress()) mACAddress(decltype(std::declval<Base>().mACAddress()) value) override
        {
            auto result = Base::mACAddress();
            if (value != result)
            {
                if (!validateMACAddress(value))
                {
                    namespace error =
                        sdbusplus::xyz::openbmc_project::Common::Error;
                    namespace metadata =
                        phosphor::logging::xyz::openbmc_project::Common;
                    phosphor::logging::report<error::InvalidArgument>(
                        metadata::InvalidArgument::ARGUMENT_NAME("mACAddress"),
                        metadata::InvalidArgument::ARGUMENT_VALUE(value.c_str()));
                    return result;
                }
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::mACAddress(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::mACAddress;

    private:
        fs::path path;

        bool validateMACAddress(decltype(std::declval<Base>().mACAddress()) value)
        {
            bool matched = false;
            std::string err = "Input parameter for MACAddress is invalid ";
            std::regex regexToCheck("^([0-9A-F]{2}[:-]){5}([0-9A-F]{2})$");
            matched = std::regex_search(value, regexToCheck);
            if (!matched)
            {
                err += "Input: " + value + " not in the format of this regex: "
                       "^([0-9A-F]{2}[:-]){5}([0-9A-F]{2})$";
            }
            if (!matched)
            {
                using namespace phosphor::logging;
                log<level::ERR>(err.c_str());
            }
            return matched;
        }
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.mACAddress());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.mACAddress()) MACAddress{};
    a(MACAddress);
    setting.mACAddress(MACAddress);
}

} // namespace MACAddress
} // namespace Network
} // namespace openbmc_project
} // namespace xyz
namespace xyz
{
namespace openbmc_project
{
namespace Control
{
namespace Power
{
namespace Cap
{

using Base = sdbusplus::xyz::openbmc_project::Control::Power::server::Cap;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Control::Power::server::Cap>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().powerCap()) powerCap(decltype(std::declval<Base>().powerCap()) value) override
        {
            auto result = Base::powerCap();
            if (value != result)
            {
                if (!validatePowerCap(value))
                {
                    namespace error =
                        sdbusplus::xyz::openbmc_project::Common::Error;
                    namespace metadata =
                        phosphor::logging::xyz::openbmc_project::Common;
                    phosphor::logging::report<error::InvalidArgument>(
                        metadata::InvalidArgument::ARGUMENT_NAME("powerCap"),
                        metadata::InvalidArgument::ARGUMENT_VALUE(std::to_string(value).c_str()));
                    return result;
                }
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::powerCap(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::powerCap;

        decltype(std::declval<Base>().powerCapEnable()) powerCapEnable(decltype(std::declval<Base>().powerCapEnable()) value) override
        {
            auto result = Base::powerCapEnable();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::powerCapEnable(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::powerCapEnable;

    private:
        fs::path path;

        bool validatePowerCap(decltype(std::declval<Base>().powerCap()) value)
        {
            bool matched = false;
            std::string err = "Input parameter for PowerCap is invalid ";
            if ((value <= 1000) && (value >= 0))
            {
                matched = true;
            }
            else
            {
                err += "Input: " + std::to_string(value) + "in uint: "
                       "Watts is not in range: "
                       "0..1000";
            }
            if (!matched)
            {
                using namespace phosphor::logging;
                log<level::ERR>(err.c_str());
            }
            return matched;
        }
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.powerCap(),setting.powerCapEnable());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.powerCap()) PowerCap{};
    decltype(setting.powerCapEnable()) PowerCapEnable{};
    a(PowerCap,PowerCapEnable);
    setting.powerCap(PowerCap);
    setting.powerCapEnable(PowerCapEnable);
}

} // namespace Cap
} // namespace Power
} // namespace Control
} // namespace openbmc_project
} // namespace xyz
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
                    std::make_unique<xyz::openbmc_project::Network::MACAddress::Impl>(
                        bus,
                        "/xyz/openbmc_project/network/host0/intf"),
                    std::make_unique<xyz::openbmc_project::Control::Boot::Mode::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/boot_mode"),
                    std::make_unique<xyz::openbmc_project::Control::Boot::Mode::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host1/boot_mode"),
                    std::make_unique<xyz::openbmc_project::Control::Power::Cap::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/power_cap"));

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<0>(settings));
            }
            else
            {
                std::get<0>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::MACAddress::mACAddress("00:00:00:00:00:00");
            }
            std::get<0>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/boot_mode";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<1>(settings));
            }
            else
            {
                std::get<1>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Safe);
            }
            std::get<1>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host1/boot_mode";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<2>(settings));
            }
            else
            {
                std::get<2>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Regular);
            }
            std::get<2>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_cap";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<3>(settings));
            }
            else
            {
                std::get<3>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCap(0);
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_cap";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<3>(settings));
            }
            else
            {
                std::get<3>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCapEnable(false);
            }
            std::get<3>(settings)->emit_object_added();

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<xyz::openbmc_project::Network::MACAddress::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Mode::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Mode::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Power::Cap::Impl>> settings;
};

} // namespace settings
} // namespace phosphor
