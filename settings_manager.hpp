// WARNING: Generated header. Do not edit!
#pragma once

#include <cereal/archives/json.hpp>
#include <fstream>
#include <utility>
#include <experimental/filesystem>
#include <regex>
#include "config.h"

#include "xyz/openbmc_project/Network/MACAddress/server.hpp"
#include "xyz/openbmc_project/Network/IP/server.hpp"
#include "xyz/openbmc_project/Control/Boot/Mode/server.hpp"


namespace phosphor
{
namespace settings
{

namespace fs = std::experimental::filesystem;

using namespace sdbusplus::xyz::openbmc_project::Network::server;
using namespace sdbusplus::xyz::openbmc_project::Control::Boot::server;

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
            if ((value != result)&&(ValidateMACAddress(value)))
            {
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
            if ((value != result)&&(ValidatePrefixLength(value)))
            {
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

        decltype(std::declval<Base>().gateway()) gateway(decltype(std::declval<Base>().gateway()) value) override
        {
            auto result = Base::gateway();
            if ((value != result)&&(ValidateGateway(value)))
            {
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
            if ((value != result)&&(ValidateAddress(value)))
            {
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
                std::string rangeToCheck("set(['0..5'])");
                std::size_t pos = rangeToCheck.rfind("..");
                int low = std::stoi(rangeToCheck.substr(0,pos));
                int high = std::stoi(rangeToCheck.substr(pos+2));
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
    a(setting.origin(),setting.prefixLength(),setting.gateway(),setting.address());
}

template<class Archive>
void load(Archive& a,
          Impl& setting)
{
    decltype(setting.origin()) Origin{};
    decltype(setting.prefixLength()) PrefixLength{};
    decltype(setting.gateway()) Gateway{};
    decltype(setting.address()) Address{};
    a(Origin,PrefixLength,Gateway,Address);
    setting.origin(Origin);
    setting.prefixLength(PrefixLength);
    setting.gateway(Gateway);
    setting.address(Address);
}

} // namespace IP
} // namespace Network
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
                    std::make_unique<xyz::openbmc_project::Network::IP::Impl>(
                        bus,
                        "/xyz/openbmc_project/network/host0/intf/addr"),
                    std::make_unique<xyz::openbmc_project::Control::Boot::Mode::Impl>(
                        bus,
                        "/xyz/openbmc_project/control/host1/boot_mode"));

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

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<2>(settings));
            }
            else
            {
                std::get<2>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::origin(IP::AddressOrigin::Static);
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<2>(settings));
            }
            else
            {
                std::get<2>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::prefixLength(0);
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<2>(settings));
            }
            else
            {
                std::get<2>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::gateway("0.0.0.0");
            }
            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/network/host0/intf/addr";
            if (fs::exists(path))
            {
                std::ifstream is(path.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*std::get<2>(settings));
            }
            else
            {
                std::get<2>(settings)->
                    sdbusplus::xyz::openbmc_project::Network::server::IP::address("0.0.0.0");
            }
            std::get<2>(settings)->emit_object_added();

            path = fs::path(SETTINGS_PERSIST_PATH) / "/xyz/openbmc_project/control/host1/boot_mode";
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

        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
            std::unique_ptr<xyz::openbmc_project::Network::MACAddress::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Mode::Impl>,
            std::unique_ptr<xyz::openbmc_project::Network::IP::Impl>,
            std::unique_ptr<xyz::openbmc_project::Control::Boot::Mode::Impl>> settings;
};

} // namespace settings
} // namespace phosphor
