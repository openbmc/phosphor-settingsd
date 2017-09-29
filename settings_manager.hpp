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

#include "xyz/openbmc_project/Control/Power/RestorePolicy/server.hpp"
#include "xyz/openbmc_project/Network/MACAddress/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Mode/server.hpp"
#include "xyz/openbmc_project/Control/Security/RestrictionMode/server.hpp"
#include "xyz/openbmc_project/Network/IP/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Source/server.hpp"
#include "xyz/openbmc_project/Time/Synchronization/server.hpp"
#include "xyz/openbmc_project/Control/TPM/Policy/server.hpp"
#include "xyz/openbmc_project/Control/MinimumShipLevel/server.hpp"
#include "xyz/openbmc_project/Control/Boot/RebootPolicy/server.hpp"
#include "xyz/openbmc_project/Time/Owner/server.hpp"
#include "xyz/openbmc_project/Control/Power/Cap/server.hpp"
#include "xyz/openbmc_project/Object/Enable/server.hpp"


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

using namespace sdbusplus::xyz::openbmc_project::Control::server;
using namespace sdbusplus::xyz::openbmc_project::Object::server;
using namespace sdbusplus::xyz::openbmc_project::Time::server;
using namespace sdbusplus::xyz::openbmc_project::Control::TPM::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Power::server;
using namespace sdbusplus::xyz::openbmc_project::Network::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Boot::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Security::server;

namespace xyz
{
namespace openbmc_project
{
namespace time
{
namespace owner
{

using Iface0 = sdbusplus::xyz::openbmc_project::Time::server::Owner;
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

        decltype(std::declval<Iface0>().timeOwner()) timeOwner(decltype(std::declval<Iface0>().timeOwner()) value) override
        {
            auto result = Iface0::timeOwner();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::timeOwner(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::timeOwner;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.timeOwner());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.timeOwner()) TimeOwner{};

    a(TimeOwner);

    setting.timeOwner(TimeOwner);
}

} // namespace owner
} // namespace time
} // namespace openbmc_project
} // namespace xyz

namespace xyz
{
namespace openbmc_project
{
namespace time
{
namespace sync_method
{

using Iface0 = sdbusplus::xyz::openbmc_project::Time::server::Synchronization;
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

        decltype(std::declval<Iface0>().timeSyncMethod()) timeSyncMethod(decltype(std::declval<Iface0>().timeSyncMethod()) value) override
        {
            auto result = Iface0::timeSyncMethod();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::timeSyncMethod(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::timeSyncMethod;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.timeSyncMethod());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.timeSyncMethod()) TimeSyncMethod{};

    a(TimeSyncMethod);

    setting.timeSyncMethod(TimeSyncMethod);
}

} // namespace sync_method
} // namespace time
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
namespace power_restore_policy
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Power::server::RestorePolicy;
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

        decltype(std::declval<Iface0>().powerRestorePolicy()) powerRestorePolicy(decltype(std::declval<Iface0>().powerRestorePolicy()) value) override
        {
            auto result = Iface0::powerRestorePolicy();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::powerRestorePolicy(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::powerRestorePolicy;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.powerRestorePolicy());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.powerRestorePolicy()) PowerRestorePolicy{};

    a(PowerRestorePolicy);

    setting.powerRestorePolicy(PowerRestorePolicy);
}

} // namespace power_restore_policy
} // namespace host0
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
namespace restriction_mode
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Security::server::RestrictionMode;
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

        decltype(std::declval<Iface0>().restrictionMode()) restrictionMode(decltype(std::declval<Iface0>().restrictionMode()) value) override
        {
            auto result = Iface0::restrictionMode();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::restrictionMode(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::restrictionMode;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.restrictionMode());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.restrictionMode()) RestrictionMode{};

    a(RestrictionMode);

    setting.restrictionMode(RestrictionMode);
}

} // namespace restriction_mode
} // namespace host0
} // namespace control
} // namespace openbmc_project
} // namespace xyz

namespace xyz
{
namespace openbmc_project
{
namespace control
{
namespace minimum_ship_level_required
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::server::MinimumShipLevel;
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

        decltype(std::declval<Iface0>().minimumShipLevelRequired()) minimumShipLevelRequired(decltype(std::declval<Iface0>().minimumShipLevelRequired()) value) override
        {
            auto result = Iface0::minimumShipLevelRequired();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::minimumShipLevelRequired(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::minimumShipLevelRequired;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.minimumShipLevelRequired());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.minimumShipLevelRequired()) MinimumShipLevelRequired{};

    a(MinimumShipLevelRequired);

    setting.minimumShipLevelRequired(MinimumShipLevelRequired);
}

} // namespace minimum_ship_level_required
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
            std::regex regexToCheck("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
            matched = std::regex_search(value, regexToCheck);
            if (!matched)
            {
                std::string err = "Input parameter for MACAddress is invalid "
                    "Input: " + value + " not in the format of this regex: "
                    "^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$";
                using namespace phosphor::logging;
                log<level::ERR>(err.c_str());
            }
            return matched;
        }
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.mACAddress());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
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
namespace network
{
namespace host0
{
namespace intf
{
namespace addr
{

using Iface0 = sdbusplus::xyz::openbmc_project::Network::server::IP;
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

        decltype(std::declval<Iface0>().origin()) origin(decltype(std::declval<Iface0>().origin()) value) override
        {
            auto result = Iface0::origin();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::origin(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::origin;

        decltype(std::declval<Iface0>().prefixLength()) prefixLength(decltype(std::declval<Iface0>().prefixLength()) value) override
        {
            auto result = Iface0::prefixLength();
            if (value != result)
            {
                if (!validatePrefixLength(value))
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
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::prefixLength(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::prefixLength;

        decltype(std::declval<Iface0>().type()) type(decltype(std::declval<Iface0>().type()) value) override
        {
            auto result = Iface0::type();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::type(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::type;

        decltype(std::declval<Iface0>().gateway()) gateway(decltype(std::declval<Iface0>().gateway()) value) override
        {
            auto result = Iface0::gateway();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::gateway(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::gateway;

        decltype(std::declval<Iface0>().address()) address(decltype(std::declval<Iface0>().address()) value) override
        {
            auto result = Iface0::address();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::address(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::address;

    private:
        fs::path path;

        bool validatePrefixLength(decltype(std::declval<Iface0>().prefixLength()) value)
        {
            bool matched = false;
            if ((value <= 128) && (value >= 0))
            {
                matched = true;
            }
            else
            {
                std::string err = "Input parameter for PrefixLength is invalid "
                    "Input: " + std::to_string(value) + "in uint: "
                    "bits is not in range:0..128";
                using namespace phosphor::logging;
                log<level::ERR>(err.c_str());
            }
            return matched;
        }
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.origin(), setting.prefixLength(), setting.type(), setting.gateway(), setting.address());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.origin()) Origin{};
    decltype(setting.prefixLength()) PrefixLength{};
    decltype(setting.type()) Type{};
    decltype(setting.gateway()) Gateway{};
    decltype(setting.address()) Address{};

    a(Origin, PrefixLength, Type, Gateway, Address);

    setting.origin(Origin);
    setting.prefixLength(PrefixLength);
    setting.type(Type);
    setting.gateway(Gateway);
    setting.address(Address);
}

} // namespace addr
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
namespace host0
{
namespace auto_reboot
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Boot::server::RebootPolicy;
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

        decltype(std::declval<Iface0>().autoReboot()) autoReboot(decltype(std::declval<Iface0>().autoReboot()) value) override
        {
            auto result = Iface0::autoReboot();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::autoReboot(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::autoReboot;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.autoReboot());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.autoReboot()) AutoReboot{};

    a(AutoReboot);

    setting.autoReboot(AutoReboot);
}

} // namespace auto_reboot
} // namespace host0
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
namespace boot
{
namespace one_time
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Source;
using Iface1 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode;
using Iface2 = sdbusplus::xyz::openbmc_project::Object::server::Enable;
using Parent = sdbusplus::server::object::object<Iface0, Iface1, Iface2>;

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus::bus& bus, const char* path):
            Parent(bus, path, true),
            path(path)
        {
        }
        virtual ~Impl() = default;

        decltype(std::declval<Iface0>().bootSource()) bootSource(decltype(std::declval<Iface0>().bootSource()) value) override
        {
            auto result = Iface0::bootSource();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::bootSource(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::bootSource;

        decltype(std::declval<Iface1>().bootMode()) bootMode(decltype(std::declval<Iface1>().bootMode()) value) override
        {
            auto result = Iface1::bootMode();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface1::bootMode(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface1::bootMode;

        decltype(std::declval<Iface2>().enabled()) enabled(decltype(std::declval<Iface2>().enabled()) value) override
        {
            auto result = Iface2::enabled();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface2::enabled(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface2::enabled;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.bootSource(), setting.bootMode(), setting.enabled());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.bootSource()) BootSource{};
    decltype(setting.bootMode()) BootMode{};
    decltype(setting.enabled()) Enabled{};

    a(BootSource, BootMode, Enabled);

    setting.bootSource(BootSource);
    setting.bootMode(BootMode);
    setting.enabled(Enabled);
}

} // namespace one_time
} // namespace boot
} // namespace host0
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
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.powerCap(), setting.powerCapEnable());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
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

using Iface0 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Source;
using Iface1 = sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode;
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

        decltype(std::declval<Iface0>().bootSource()) bootSource(decltype(std::declval<Iface0>().bootSource()) value) override
        {
            auto result = Iface0::bootSource();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::bootSource(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::bootSource;

        decltype(std::declval<Iface1>().bootMode()) bootMode(decltype(std::declval<Iface1>().bootMode()) value) override
        {
            auto result = Iface1::bootMode();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface1::bootMode(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface1::bootMode;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.bootSource(), setting.bootMode());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.bootSource()) BootSource{};
    decltype(setting.bootMode()) BootMode{};

    a(BootSource, BootMode);

    setting.bootSource(BootSource);
    setting.bootMode(BootMode);
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
namespace control
{
namespace host0
{
namespace TPMEnable
{

using Iface0 = sdbusplus::xyz::openbmc_project::Control::TPM::server::Policy;
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

        decltype(std::declval<Iface0>().tPMEnable()) tPMEnable(decltype(std::declval<Iface0>().tPMEnable()) value) override
        {
            auto result = Iface0::tPMEnable();
            if (value != result)
            {
                fs::path p(SETTINGS_PERSIST_PATH);
                p /= path;
                p += persistent::fileSuffix;
                fs::create_directories(p.parent_path());
                std::ofstream os(p.c_str(), std::ios::binary);
                cereal::JSONOutputArchive oarchive(os);
                result = Iface0::tPMEnable(value);
                oarchive(*this);
            }
            return result;
        }
        using Iface0::tPMEnable;

    private:
        fs::path path;
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          const std::uint32_t version)
{
    a(setting.tPMEnable());
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    decltype(setting.tPMEnable()) TPMEnable{};

    a(TPMEnable);

    setting.tPMEnable(TPMEnable);
}

} // namespace TPMEnable
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
                    std::make_unique<xyz::openbmc_project::time::owner::Impl>(
                        bus,
                        "/xyz/openbmc_project/time/owner"),
                    std::make_unique<xyz::openbmc_project::time::sync_method::Impl>(
                        bus,
                        "/xyz/openbmc_project/time/sync_method"),
                    std::make_unique<xyz::openbmc_project::control::host0::power_restore_policy::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/power_restore_policy"),
                    std::make_unique<xyz::openbmc_project::control::host0::restriction_mode::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/restriction_mode"),
                    std::make_unique<xyz::openbmc_project::control::minimum_ship_level_required::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/minimum_ship_level_required"),
                    std::make_unique<xyz::openbmc_project::network::host0::intf::Impl>(
                        bus,
                        "/xyz/openbmc_project/network/host0/intf"),
                    std::make_unique<xyz::openbmc_project::network::host0::intf::addr::Impl>(
                        bus,
                        "/xyz/openbmc_project/network/host0/intf/addr"),
                    std::make_unique<xyz::openbmc_project::control::host0::auto_reboot::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/auto_reboot"),
                    std::make_unique<xyz::openbmc_project::control::host0::boot::one_time::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/boot/one_time"),
                    std::make_unique<xyz::openbmc_project::control::host0::power_cap::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/power_cap"),
                    std::make_unique<xyz::openbmc_project::control::host0::boot::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/boot"),
                    std::make_unique<xyz::openbmc_project::control::host0::TPMEnable::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host0/TPMEnable"));

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/time/owner";
            path += persistent::fileSuffix;
            auto initSetting0 = [&]()
            {
                std::get<0>(settings)->
                  sdbusplus::xyz::openbmc_project::Time::server::Owner::timeOwner(Owner::Owners::BMC);
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

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/time/sync_method";
            path += persistent::fileSuffix;
            auto initSetting1 = [&]()
            {
                std::get<1>(settings)->
                  sdbusplus::xyz::openbmc_project::Time::server::Synchronization::timeSyncMethod(Synchronization::Method::NTP);
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

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_restore_policy";
            path += persistent::fileSuffix;
            auto initSetting2 = [&]()
            {
                std::get<2>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Power::server::RestorePolicy::powerRestorePolicy(RestorePolicy::Policy::AlwaysOff);
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

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/restriction_mode";
            path += persistent::fileSuffix;
            auto initSetting3 = [&]()
            {
                std::get<3>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Security::server::RestrictionMode::restrictionMode(RestrictionMode::Modes::None);
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

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/minimum_ship_level_required";
            path += persistent::fileSuffix;
            auto initSetting4 = [&]()
            {
                std::get<4>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::server::MinimumShipLevel::minimumShipLevelRequired(true);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<4>(settings));
                }
                else
                {
                    initSetting4();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting4();
            }
            std::get<4>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf";
            path += persistent::fileSuffix;
            auto initSetting5 = [&]()
            {
                std::get<5>(settings)->
                  sdbusplus::xyz::openbmc_project::Network::server::MACAddress::mACAddress("00:00:00:00:00:00");
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<5>(settings));
                }
                else
                {
                    initSetting5();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting5();
            }
            std::get<5>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            path += persistent::fileSuffix;
            auto initSetting6 = [&]()
            {
                std::get<6>(settings)->
                  sdbusplus::xyz::openbmc_project::Network::server::IP::origin(IP::AddressOrigin::Static);
                std::get<6>(settings)->
                  sdbusplus::xyz::openbmc_project::Network::server::IP::prefixLength(0);
                std::get<6>(settings)->
                  sdbusplus::xyz::openbmc_project::Network::server::IP::type(IP::Protocol::IPv4);
                std::get<6>(settings)->
                  sdbusplus::xyz::openbmc_project::Network::server::IP::gateway("0.0.0.0");
                std::get<6>(settings)->
                  sdbusplus::xyz::openbmc_project::Network::server::IP::address("0.0.0.0");
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<6>(settings));
                }
                else
                {
                    initSetting6();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting6();
            }
            std::get<6>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/auto_reboot";
            path += persistent::fileSuffix;
            auto initSetting7 = [&]()
            {
                std::get<7>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::RebootPolicy::autoReboot(true);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<7>(settings));
                }
                else
                {
                    initSetting7();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting7();
            }
            std::get<7>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/boot/one_time";
            path += persistent::fileSuffix;
            auto initSetting8 = [&]()
            {
                std::get<8>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Source::bootSource(Source::Sources::Default);
                std::get<8>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Regular);
                std::get<8>(settings)->
                  sdbusplus::xyz::openbmc_project::Object::server::Enable::enabled(true);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<8>(settings));
                }
                else
                {
                    initSetting8();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting8();
            }
            std::get<8>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/power_cap";
            path += persistent::fileSuffix;
            auto initSetting9 = [&]()
            {
                std::get<9>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCap(0);
                std::get<9>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Power::server::Cap::powerCapEnable(false);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<9>(settings));
                }
                else
                {
                    initSetting9();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting9();
            }
            std::get<9>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/boot";
            path += persistent::fileSuffix;
            auto initSetting10 = [&]()
            {
                std::get<10>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Source::bootSource(Source::Sources::Default);
                std::get<10>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::Boot::server::Mode::bootMode(Mode::Modes::Regular);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<10>(settings));
                }
                else
                {
                    initSetting10();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting10();
            }
            std::get<10>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host0/TPMEnable";
            path += persistent::fileSuffix;
            auto initSetting11 = [&]()
            {
                std::get<11>(settings)->
                  sdbusplus::xyz::openbmc_project::Control::TPM::server::Policy::tPMEnable(false);
            };

            try
            {
                if (fs::exists(path))
                {
                    std::ifstream is(path.c_str(), std::ios::in);
                    cereal::JSONInputArchive iarchive(is);
                    iarchive(*std::get<11>(settings));
                }
                else
                {
                    initSetting11();
                }
            }
            catch (cereal::Exception& e)
            {
                log<level::ERR>(e.what());
                fs::remove(path);
                initSetting11();
            }
            std::get<11>(settings)->emit_object_added();

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<xyz::openbmc_project::time::owner::Impl>,
            std::unique_ptr<xyz::openbmc_project::time::sync_method::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::power_restore_policy::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::restriction_mode::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::minimum_ship_level_required::Impl>,
            std::unique_ptr<xyz::openbmc_project::network::host0::intf::Impl>,
            std::unique_ptr<xyz::openbmc_project::network::host0::intf::addr::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::auto_reboot::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::boot::one_time::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::power_cap::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::boot::Impl>,
            std::unique_ptr<xyz::openbmc_project::control::host0::TPMEnable::Impl>> settings;
};

} // namespace settings
} // namespace phosphor

// Now register the class version with Cereal
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::time::owner::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::time::sync_method::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::host0::power_restore_policy::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::host0::restriction_mode::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::minimum_ship_level_required::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::network::host0::intf::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::network::host0::intf::addr::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::host0::auto_reboot::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::host0::boot::one_time::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::host0::power_cap::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::host0::boot::Impl, CLASS_VERSION);
CEREAL_CLASS_VERSION(phosphor::settings::xyz::openbmc_project::control::host0::TPMEnable::Impl, CLASS_VERSION);
