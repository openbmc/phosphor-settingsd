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
using namespace phosphor::logging;

#include "xyz/openbmc_project/Network/MACAddress/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Source/server.hpp"
#include "xyz/openbmc_project/Control/Power/Cap/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Mode/server.hpp"


namespace phosphor
{
namespace settings
{

namespace fs = std::experimental::filesystem;

namespace persistent
{

// A setting d-bus object /foo/bar/baz is persisted in the filesystem with the
// same path. This eases re-construction of settings objects when we restore
// from the filesystem. This can be a problem though when you have two objects
// such as - /foo/bar and /foo/bar/baz. This is because 'bar' will be treated as
// a file in the first case, and a subdir in the second. To solve this, suffix
// files with a trailing __. The __ is a safe character sequence to use, because
// we won't have d-bus object paths ending with this.
// With this the objects would be persisted as - /foo/bar__ and /foo/bar/baz__.
constexpr auto fileSuffix = "__";

}

using namespace sdbusplus::xyz::openbmc_project::Network::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Boot::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Power::server;

namespace xyz
{
namespace openbmc_project
{
namespace control
{
namespace host0
{
namespace boot
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode;
using Iface1 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Source;
using Parent = sdbusplus::server::object::object<Iface0, Iface1>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Iface0>().bootMode()) bootMode(decltype(std::declval<Iface0>().bootMode()) value) override
        {
            auto result = Iface0::bootMode();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::bootMode(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::bootMode;

        decltype(std::declval<Iface1>().bootSource()) bootSource(decltype(std::declval<Iface1>().bootSource()) value) override
        {
            auto result = Iface1::bootSource();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface1::bootSource(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface1::bootSource;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.bootMode(), setting.bootSource());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.bootMode()) BootMode{};
    decltype(setting.bootSource()) BootSource{};

    a(BootMode, BootSource);

    setting.bootMode(BootMode);
    setting.bootSource(BootSource);
}

} // namespace boot
} // namespace host0
} // namespace control
} // namespace openbmc_project
} // namespace xyz

namespace xyz
{
namespace openbmc_project
{
namespace network
{
namespace host0
{
namespace intf
{

using Iface0 = sdbusplus::xyz::openbmc_project::Network::server::MACAddress;
using Parent = sdbusplus::server::object::object<Iface0>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Iface0>().mACAddress()) mACAddress(decltype(std::declval<Iface0>().mACAddress()) value) override
        {
            auto result = Iface0::mACAddress();
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
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::mACAddress(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::mACAddress;

    private:
        fs::path path;

        bool validateMACAddress(decltype(std::declval<Iface0>().mACAddress()) value)
        {
            bool matched = false;
            std::regex regexToCheck("^([0-9A-F]{2}[:-]){5}([0-9A-F]{2})$");
            matched = std::regex_search(value, regexToCheck);
            if (!matched)
            {
                std::string err = "Input parameter for MACAddress is invalid "
                    "Input: " + value + " not in the format of this regex: "
                    "^([0-9A-F]{2}[:-]){5}([0-9A-F]{2})$";
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

} // namespace intf
} // namespace host0
} // namespace network
} // namespace openbmc_project
} // namespace xyz

namespace xyz
{
namespace openbmc_project
{
namespace control
{
namespace host1
{
namespace boot
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode;
using Iface1 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Source;
using Parent = sdbusplus::server::object::object<Iface0, Iface1>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Iface0>().bootMode()) bootMode(decltype(std::declval<Iface0>().bootMode()) value) override
        {
            auto result = Iface0::bootMode();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::bootMode(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::bootMode;

        decltype(std::declval<Iface1>().bootSource()) bootSource(decltype(std::declval<Iface1>().bootSource()) value) override
        {
            auto result = Iface1::bootSource();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface1::bootSource(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface1::bootSource;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.bootMode(), setting.bootSource());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.bootMode()) BootMode{};
    decltype(setting.bootSource()) BootSource{};

    a(BootMode, BootSource);

    setting.bootMode(BootMode);
    setting.bootSource(BootSource);
}

} // namespace boot
} // namespace host1
} // namespace control
} // namespace openbmc_project
} // namespace xyz

namespace xyz
{
namespace openbmc_project
{
namespace control
{
namespace host0
{
namespace power_cap
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Power::server::Cap;
using Parent = sdbusplus::server::object::object<Iface0>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Iface0>().powerCap()) powerCap(decltype(std::declval<Iface0>().powerCap()) value) override
        {
            auto result = Iface0::powerCap();
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
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::powerCap(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::powerCap;

        decltype(std::declval<Iface0>().powerCapEnable()) powerCapEnable(decltype(std::declval<Iface0>().powerCapEnable()) value) override
        {
            auto result = Iface0::powerCapEnable();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::powerCapEnable(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::powerCapEnable;

    private:
        fs::path path;

        bool validatePowerCap(decltype(std::declval<Iface0>().powerCap()) value)
        {
            bool matched = false;
            if ((value <= 1000) && (value >= 0))
            {
                matched = true;
            }
            else
            {
                std::string err = "Input parameter for PowerCap is invalid "
                    "Input: " + std::to_string(value) + "in uint: "
                    "Watts is not in range:0..1000";
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
    a(setting.powerCap(), setting.powerCapEnable());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.powerCap()) PowerCap{};
    decltype(setting.powerCapEnable()) PowerCapEnable{};

    a(PowerCap, PowerCapEnable);

    setting.powerCap(PowerCap);
    setting.powerCapEnable(PowerCapEnable);
}

} // namespace power_cap
} // namespace host0
} // namespace control
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
                    std::make_unique<xyz::openbmc_project::control::host0::boot::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/boot"),
                    std::make_unique<xyz::openbmc_project::network::host0::intf::Impl>(
                        bus,
                        "/xyz/openbmc_project/network/host0/intf"),
                    std::make_unique<xyz::openbmc_project::control::host1::boot::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host1/boot"),
                    std::make_unique<xyz::openbmc_project::control::host0::power_cap::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/power_cap"));

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/boot";
            path += persistent::fileSuffix;
            auto initSetting0 = [&]()
            {
                std::get<0>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Safe);
                std::get<0>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Source::bootSource(Source::Sources::Default);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<0>(settings));
                }
                else
                {
                    initSetting0();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting0();
            }
            std::get<0>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf";
            path += persistent::fileSuffix;
            auto initSetting1 = [&]()
            {
                std::get<1>(settings)->
                  sdbusplus::xyz::openbmc_project::Network::server::MACAddress::mACAddress("00:00:00:00:00:00");
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<1>(settings));
                }
                else
                {
                    initSetting1();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting1();
            }
            std::get<1>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host1/boot";
            path += persistent::fileSuffix;
            auto initSetting2 = [&]()
            {
                std::get<2>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Safe);
                std::get<2>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Source::bootSource(Source::Sources::Default);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<2>(settings));
                }
                else
                {
                    initSetting2();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting2();
            }
            std::get<2>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_cap";
            path += persistent::fileSuffix;
            auto initSetting3 = [&]()
            {
                std::get<3>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCap(0);
                std::get<3>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCapEnable(false);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<3>(settings));
                }
                else
                {
                    initSetting3();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting3();
            }
            std::get<3>(settings)->emit_object_added();

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<xyz::openbmc_project::control::host0::boot::Impl>,
            std::unique_ptr<xyz::openbmc_project::network::host0::intf::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host1::boot::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::power_cap::Impl>> settings;
};

} // namespace settings
} // namespace phosphor
