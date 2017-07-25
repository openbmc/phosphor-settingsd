// WARNING: Generated header. Do not edit!
#pragma once

#include <cereal/archives/json.hpp>
#include <fstream>
#include <utility>
#include <experimental/filesystem>
#include <regex>
#include <phosphor-logging/elog.hpp>
#include <phosphor-logging/elog-errors.hpp>
#include "config.h"
#include <xyz/openbmc_project/Common/error.hpp>

#include "xyz/openbmc_project/Control/Boot/RebootPolicy/server.hpp"
#include "xyz/openbmc_project/Control/Power/RestorePolicy/server.hpp"
#include "xyz/openbmc_project/Network/MACAddress/server.hpp"
#include "xyz/openbmc_project/Network/IP/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Source/server.hpp"
#include "xyz/openbmc_project/Time/Synchronization/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Mode/server.hpp"
#include "xyz/openbmc_project/Time/Owner/server.hpp"
#include "xyz/openbmc_project/Control/Power/Cap/server.hpp"


namespace phosphor
{
namespace settings
{

namespace fs = std::experimental::filesystem;

using namespace sdbusplus::xyz::openbmc_project::Time::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Boot::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Power::server;
using namespace sdbusplus::xyz::openbmc_project::Network::server;

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
                if (!ValidatePowerCap(value))
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


        bool ValidatePowerCap(decltype(std::declval<Base>().powerCap()) value)
        {
             bool matched = false;
                std::string rangeToCheck("set(['0..10'])");
                std::size_t pos = rangeToCheck.rfind("..");
                decltype(std::declval<Base>().powerCap()) low = std::stoi(rangeToCheck.substr(0,pos));
                decltype(std::declval<Base>().powerCap()) high = std::stoi(rangeToCheck.substr(pos+2));
                if ((value <= high)&&(value >= low))
                {
                    matched = true;
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
namespace RebootPolicy
{

using Base = sdbusplus::xyz::openbmc_project::Control::Boot::server::RebootPolicy;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Control::Boot::server::RebootPolicy>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().autoReboot()) autoReboot(decltype(std::declval<Base>().autoReboot()) value) override
        {
            auto result = Base::autoReboot();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::autoReboot(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::autoReboot;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.autoReboot());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.autoReboot()) AutoReboot{};
    a(AutoReboot);
    setting.autoReboot(AutoReboot);
}

} // namespace RebootPolicy
} // namespace Boot
} // namespace Control
} // namespace openbmc_project
} // namespace xyz
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
                if (!ValidateMACAddress(value))
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


        bool ValidateMACAddress(decltype(std::declval<Base>().mACAddress()) value)
        {
             bool matched = false;
                std::smatch pieces_match;
                std::regex regexToCheck("^([0-9A-F]{2}[:-]){5}([0-9A-F]{2})$");
                matched = std::regex_match(value, pieces_match, regexToCheck);
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
namespace RestorePolicy
{

using Base = sdbusplus::xyz::openbmc_project::Control::Power::server::RestorePolicy;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Control::Power::server::RestorePolicy>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().powerRestorePolicy()) powerRestorePolicy(decltype(std::declval<Base>().powerRestorePolicy()) value) override
        {
            auto result = Base::powerRestorePolicy();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::powerRestorePolicy(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::powerRestorePolicy;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.powerRestorePolicy());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.powerRestorePolicy()) PowerRestorePolicy{};
    a(PowerRestorePolicy);
    setting.powerRestorePolicy(PowerRestorePolicy);
}

} // namespace RestorePolicy
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
namespace Source
{

using Base = sdbusplus::xyz::openbmc_project::Control::Boot::server::Source;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Control::Boot::server::Source>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().bootSource()) bootSource(decltype(std::declval<Base>().bootSource()) value) override
        {
            auto result = Base::bootSource();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::bootSource(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::bootSource;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.bootSource());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.bootSource()) BootSource{};
    a(BootSource);
    setting.bootSource(BootSource);
}

} // namespace Source
} // namespace Boot
} // namespace Control
} // namespace openbmc_project
} // namespace xyz
namespace xyz
{
namespace openbmc_project
{
namespace Time
{
namespace Synchronization
{

using Base = sdbusplus::xyz::openbmc_project::Time::server::Synchronization;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Time::server::Synchronization>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().timeSyncMethod()) timeSyncMethod(decltype(std::declval<Base>().timeSyncMethod()) value) override
        {
            auto result = Base::timeSyncMethod();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::timeSyncMethod(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::timeSyncMethod;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.timeSyncMethod());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.timeSyncMethod()) TimeSyncMethod{};
    a(TimeSyncMethod);
    setting.timeSyncMethod(TimeSyncMethod);
}

} // namespace Synchronization
} // namespace Time
} // namespace openbmc_project
} // namespace xyz
namespace xyz
{
namespace openbmc_project
{
namespace Time
{
namespace Owner
{

using Base = sdbusplus::xyz::openbmc_project::Time::server::Owner;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Time::server::Owner>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().timeOwner()) timeOwner(decltype(std::declval<Base>().timeOwner()) value) override
        {
            auto result = Base::timeOwner();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::timeOwner(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::timeOwner;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.timeOwner());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.timeOwner()) TimeOwner{};
    a(TimeOwner);
    setting.timeOwner(TimeOwner);
}

} // namespace Owner
} // namespace Time
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
namespace xyz
{
namespace openbmc_project
{
namespace Network
{
namespace IP
{

using Base = sdbusplus::xyz::openbmc_project::Network::server::IP;
using Parent = sdbusplus::server::object::object<sdbusplus::xyz::openbmc_project::Network::server::IP>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Base>().origin()) origin(decltype(std::declval<Base>().origin()) value) override
        {
            auto result = Base::origin();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::origin(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::origin;

        decltype(std::declval<Base>().prefixLength()) prefixLength(decltype(std::declval<Base>().prefixLength()) value) override
        {
            auto result = Base::prefixLength();
            if (value != result)
            {
                if (!ValidatePrefixLength(value))
                {
                    namespace error =
                        sdbusplus::xyz::openbmc_project::Common::Error;
                    namespace metadata =
                        phosphor::logging::xyz::openbmc_project::Common;
                    phosphor::logging::report<error::InvalidArgument>(
                        metadata::InvalidArgument::ARGUMENT_NAME("prefixLength"),
                        metadata::InvalidArgument::ARGUMENT_VALUE(std::to_string(value).c_str()));
                    return result;
                }
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::prefixLength(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::prefixLength;

        decltype(std::declval<Base>().type()) type(decltype(std::declval<Base>().type()) value) override
        {
            auto result = Base::type();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::type(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::type;

        decltype(std::declval<Base>().gateway()) gateway(decltype(std::declval<Base>().gateway()) value) override
        {
            auto result = Base::gateway();
            if (value != result)
            {
                if (!ValidateGateway(value))
                {
                    namespace error =
                        sdbusplus::xyz::openbmc_project::Common::Error;
                    namespace metadata =
                        phosphor::logging::xyz::openbmc_project::Common;
                    phosphor::logging::report<error::InvalidArgument>(
                        metadata::InvalidArgument::ARGUMENT_NAME("gateway"),
                        metadata::InvalidArgument::ARGUMENT_VALUE(value.c_str()));
                    return result;
                }
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::gateway(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::gateway;

        decltype(std::declval<Base>().address()) address(decltype(std::declval<Base>().address()) value) override
        {
            auto result = Base::address();
            if (value != result)
            {
                if (!ValidateAddress(value))
                {
                    namespace error =
                        sdbusplus::xyz::openbmc_project::Common::Error;
                    namespace metadata =
                        phosphor::logging::xyz::openbmc_project::Common;
                    phosphor::logging::report<error::InvalidArgument>(
                        metadata::InvalidArgument::ARGUMENT_NAME("address"),
                        metadata::InvalidArgument::ARGUMENT_VALUE(value.c_str()));
                    return result;
                }
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Base::address(value);
                oarchive(*this);
            }
            return result;
        }
        using Base::address;

    private:
        fs::path path;


        bool ValidatePrefixLength(decltype(std::declval<Base>().prefixLength()) value)
        {
             bool matched = false;
                std::string rangeToCheck("set(['0..10'])");
                std::size_t pos = rangeToCheck.rfind("..");
                decltype(std::declval<Base>().prefixLength()) low = std::stoi(rangeToCheck.substr(0,pos));
                decltype(std::declval<Base>().prefixLength()) high = std::stoi(rangeToCheck.substr(pos+2));
                if ((value <= high)&&(value >= low))
                {
                    matched = true;
                }
            return matched;
        }


        bool ValidateGateway(decltype(std::declval<Base>().gateway()) value)
        {
             bool matched = false;
                std::smatch pieces_match;
                std::regex regexToCheck("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
                matched = std::regex_match(value, pieces_match, regexToCheck);
            return matched;
        }


        bool ValidateAddress(decltype(std::declval<Base>().address()) value)
        {
             bool matched = false;
                std::smatch pieces_match;
                std::regex regexToCheck("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
                matched = std::regex_match(value, pieces_match, regexToCheck);
            return matched;
        }
};

template<class Archive>
void save(Archive& a,
          const Impl& setting)
{
    a(setting.origin(),setting.prefixLength(),setting.type(),setting.gateway(),setting.address());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.origin()) Origin{};
    decltype(setting.prefixLength()) PrefixLength{};
    decltype(setting.type()) Type{};
    decltype(setting.gateway()) Gateway{};
    decltype(setting.address()) Address{};
    a(Origin,PrefixLength,Type,Gateway,Address);
    setting.origin(Origin);
    setting.prefixLength(PrefixLength);
    setting.type(Type);
    setting.gateway(Gateway);
    setting.address(Address);
}

} // namespace IP
} // namespace Network
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
                    std::make_unique<xyz::openbmc_project::Time::Owner::Impl>(
                        bus,
                        "/xyz/openbmc_project/time/owner"),
                    std::make_unique<xyz::openbmc_project::Time::Synchronization::Impl>(
                        bus,
                        "/xyz/openbmc_project/time/sync_method"),
                    std::make_unique<xyz::openbmc_project::Control::Power::RestorePolicy::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/power_restore_policy"),
                    std::make_unique<xyz::openbmc_project::Control::Boot::Mode::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/boot_mode"),
                    std::make_unique<xyz::openbmc_project::Control::Boot::Source::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/boot_source"),
                    std::make_unique<xyz::openbmc_project::Network::MACAddress::Impl>(
                        bus,
                        "/xyz/openbmc_project/network/host0/intf"),
                    std::make_unique<xyz::openbmc_project::Network::IP::Impl>(
                        bus,
                        "/xyz/openbmc_project/network/host0/intf/addr"),
                    std::make_unique<xyz::openbmc_project::Control::Boot::RebootPolicy::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/auto_reboot"),
                    std::make_unique<xyz::openbmc_project::Control::Power::Cap::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/power_cap"));

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/time/owner";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<0>(settings));
            }
            else
            {
                std::get<0>(settings)->
                    sdbusplus::xyz::openbmc_project::Time::server::Owner::timeOwner(Owner::Owners::BMC);
            }
            std::get<0>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/time/sync_method";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<1>(settings));
            }
            else
            {
                std::get<1>(settings)->
                    sdbusplus::xyz::openbmc_project::Time::server::Synchronization::timeSyncMethod(Synchronization::Method::NTP);
            }
            std::get<1>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_restore_policy";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<2>(settings));
            }
            else
            {
                std::get<2>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Power::server::RestorePolicy::powerRestorePolicy(RestorePolicy::Policy::Restore);
            }
            std::get<2>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/boot_mode";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<3>(settings));
            }
            else
            {
                std::get<3>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Regular);
            }
            std::get<3>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/boot_source";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<4>(settings));
            }
            else
            {
                std::get<4>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Boot::server::Source::bootSource(Source::Sources::Default);
            }
            std::get<4>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<5>(settings));
            }
            else
            {
                std::get<5>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::MACAddress::mACAddress("00:00:00:00:00:00");
            }
            std::get<5>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<6>(settings));
            }
            else
            {
                std::get<6>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::origin(IP::AddressOrigin::Static);
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<6>(settings));
            }
            else
            {
                std::get<6>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::prefixLength(0);
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<6>(settings));
            }
            else
            {
                std::get<6>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::type(IP::Protocol::IPv4);
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<6>(settings));
            }
            else
            {
                std::get<6>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::gateway("0.0.0.0");
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<6>(settings));
            }
            else
            {
                std::get<6>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::address("0.0.0.0");
            }
            std::get<6>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/auto_reboot";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<7>(settings));
            }
            else
            {
                std::get<7>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Boot::server::RebootPolicy::autoReboot(false);
            }
            std::get<7>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_cap";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<8>(settings));
            }
            else
            {
                std::get<8>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCap(0);
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_cap";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<8>(settings));
            }
            else
            {
                std::get<8>(settings)->
                    sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCapEnable(false);
            }
            std::get<8>(settings)->emit_object_added();

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<xyz::openbmc_project::Time::Owner::Impl>,
            std::unique_ptr<xyz::openbmc_project::Time::Synchronization::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Power::RestorePolicy::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Mode::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Source::Impl>,
            std::unique_ptr<xyz::openbmc_project::Network::MACAddress::Impl>,
            std::unique_ptr<xyz::openbmc_project::Network::IP::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::RebootPolicy::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Power::Cap::Impl>> settings;
};

} // namespace settings
} // namespace phosphor
