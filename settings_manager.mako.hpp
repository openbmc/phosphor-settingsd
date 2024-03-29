## This file is a template.  The comment below is emitted
## into the rendered file; feel free to edit this file.
// WARNING: Generated header. Do not edit!
<%
import re
from collections import defaultdict
from sdbusplus.namedelement import NamedElement
objects = settingsDict.keys()
sdbusplus_includes = []
props = defaultdict(list)
validators = defaultdict(tuple)

def get_setting_sdbusplus_type(setting_intf):
    setting = "sdbusplus::" + setting_intf.replace('.', '::')
    i = setting.rfind('::')
    setting = setting[:i] + '::server::' + setting[i+2:]
    return setting

def get_setting_type(path):
    path = path[1:]
    path = path.replace('/', '::')
    return path

def get_default_value(object, interface, prop):
    default_value = None
    for item in settingsDict[object]:
        if item['Interface'] == interface:
            default_value = item['Properties'][prop]['Default']
            break

    if isinstance(default_value, str) and  not \
        default_value.startswith('"') and '::' in default_value:
            ns = get_setting_sdbusplus_type(interface)
            i = ns.rfind('::')
            default_value = "{}::{}".format(ns[:i], default_value)

    return default_value
%>\
#pragma once

% for object in objects:
    % for item in settingsDict[object]:
<%
    include = item['Interface']
    include = include.replace('.', '/')
    include = include + "/server.hpp"
    sdbusplus_includes.append(include)
%>\
    % endfor
% endfor
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <utility>
#include <filesystem>
#include <regex>
#include <phosphor-logging/elog.hpp>
#include <phosphor-logging/elog-errors.hpp>
#include <phosphor-logging/lg2.hpp>
#include <xyz/openbmc_project/Common/error.hpp>

/* The DBus busname to own */
#define SETTINGS_BUSNAME "xyz.openbmc_project.Settings"
/* Path of directory housing persisted settings */
#define SETTINGS_PERSIST_PATH "/var/lib/phosphor-settings-manager/settings"

/* Class version to register with Cereal */
static constexpr size_t CLASS_VERSION = 2;
static constexpr size_t CLASS_VERSION_WITH_NVP = 2;

% for i in set(sdbusplus_includes):
#include "${i}"
% endfor

namespace phosphor
{
namespace settings
{

namespace fs = std::filesystem;

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

static fs::path getFilePath(const fs::path& objectPath)
{
    fs::path p(SETTINGS_PERSIST_PATH);
    p /= objectPath.relative_path();
    p += persistent::fileSuffix;
    return p;
}

% for object in objects:
<%
   ns = object.split('/')
   ns.pop(0)
%>\
% for n in ns:
namespace ${n}
{
% endfor
<%
    interfaces = []
    aliases = []
    for item in settingsDict[object]:
        interfaces.append(item['Interface'])
        for name, meta in item['Properties'].items():
            if 'Validation' in meta:
                dict = meta['Validation']
                if dict['Type'] == "range":
                    validators[name] = (dict['Type'], dict['Validator'], dict['Unit'])
                else:
                    validators[name] = (dict['Type'], dict['Validator'])
%>
% for index, intf in enumerate(interfaces):
using Iface${index} = ${get_setting_sdbusplus_type(intf)};
<% aliases.append("Iface" + str(index)) %>\
% endfor
<%
    parent = "sdbusplus::server::object_t" + "<" + ", ".join(aliases) + ">"
%>\
using Parent = ${parent};

class Impl : public Parent
{
    public:
        Impl(sdbusplus::bus_t& bus, const char* path):
            Parent(bus, path, Parent::action::defer_emit),
            path(path)
        {
        }
        virtual ~Impl() = default;

        void setInitialVersion(std::uint32_t v)
        {
            initialVersion = v;
        }

        std::uint32_t getInitialVersion() const
        {
            return initialVersion;
        }

        bool deserialize()
        {
            auto p = getFilePath(path);
            if (fs::exists(p))
            {
                std::ifstream is(p.c_str(), std::ios::in);
                cereal::JSONInputArchive iarchive(is);
                iarchive(*this);
                return true;
            }
            return false;
        }

        void serialize()
        {
            auto p = getFilePath(path);
            if (!fs::exists(p.parent_path()))
            {
                fs::create_directories(p.parent_path());
            }
            std::ofstream os(p.c_str(), std::ios::binary);
            cereal::JSONOutputArchive oarchive(os);
            oarchive(*this);
        }

        void removeFile() const
        {
            std::error_code ec;
            fs::remove(getFilePath(path), ec);
        }

% for index, item in enumerate(settingsDict[object]):
    % for propName, metaDict in item['Properties'].items():
<% t = NamedElement(name=propName).camelCase %>\
<% fname = "validate" + propName %>\
        decltype(std::declval<Iface${index}>().${t}()) ${t}(decltype(std::declval<Iface${index}>().${t}()) value) override
        {
            auto result = Iface${index}::${t}();
            if (value != result)
            {
            % if propName in validators:
                if (!${fname}(value))
                {
                    namespace error =
                        sdbusplus::xyz::openbmc_project::Common::Error;
                    namespace metadata =
                        phosphor::logging::xyz::openbmc_project::Common;
                    phosphor::logging::report<error::InvalidArgument>(
                        metadata::InvalidArgument::ARGUMENT_NAME("${t}"),
                    % if validators[propName][0] != "regex":
                        metadata::InvalidArgument::ARGUMENT_VALUE(std::to_string(value).c_str()));
                    % else:
                        metadata::InvalidArgument::ARGUMENT_VALUE(value.c_str()));
                    % endif
                    return result;
                }
             % endif
                result = Iface${index}::${t}(value);
                serialize();
            }
            return result;
        }
        using Iface${index}::${t};

    % endfor
% endfor
    private:
        fs::path path;
        std::uint32_t initialVersion = 0;
% for index, item in enumerate(settingsDict[object]):
  % for propName, metaDict in item['Properties'].items():
<% t = NamedElement(name=propName).camelCase %>\
<% fname = "validate" + propName %>\
    % if propName in validators:

        bool ${fname}(decltype(std::declval<Iface${index}>().${t}()) value)
        {
            bool matched = false;
        % if (validators[propName][0] == 'regex'):
            std::regex regexToCheck("${validators[propName][1]}");
            matched = std::regex_search(value, regexToCheck);
            if (!matched)
            {
                lg2::error("Input parameter for ${propName} is invalid. "
                           "Input '{VALUE}' not in the format of this regex: "
                           "${validators[propName][1]}", "VALUE", value);
            }
        % elif (validators[propName][0] == 'range'):
<% lowhigh = re.split('\.\.', validators[propName][1]) %>\
        % if lowhigh[0] == '0':
            if (value <= ${lowhigh[1]})
        % else:
            if ((value <= ${lowhigh[1]}) && (value >= ${lowhigh[0]}))
        % endif
            {
                matched = true;
            }
            else
            {
                lg2::error("Input parameter for ${propName} is invalid. "
                           "Input '{VALUE}' with unit '${validators[propName][2]}' "
                           "is not in range ${validators[propName][1]}",
                           "VALUE", std::to_string(value));
            }
        % else:
            <% assert("Unknown validation type: propName") %>\
        % endif
            return matched;
        }
    % endif
  % endfor
% endfor
};

template<class Archive>
void save(Archive& a,
          const Impl& setting,
          [[maybe_unused]] const std::uint32_t version)
{
<%
props = []
for index, item in enumerate(settingsDict[object]):
    props.extend(item['Properties'].keys())
%>\
## Since the iface isn't saved, property names need to be unique on
## the object path.  This could be supported by providing unique
## field names to make_nvp() if ever necessary.
% if len(set(props)) != len(props):
#error Duplicate property names on object path ${object}
%endif
<%
args = []
for prop in props:
    t = "setting." + NamedElement(name=prop).camelCase + "()"
    args.append(f"cereal::make_nvp(\"{prop}\", {t})")
args = ", ".join(args)
%>\
    a(${args});
}

template<class Archive>
void load(Archive& a,
          Impl& setting,
          const std::uint32_t version)
{
    setting.setInitialVersion(version);
<%
props = []
for index, item in enumerate(settingsDict[object]):
    for prop in item['Properties'].keys():
        t = "setting." + NamedElement(name=prop).camelCase + "()"
        props.append({'prop' : prop, 'iface': item['Interface'], 'func': t})
%>\
% for p in props:
    decltype(${p['func']}) ${p['prop']}{};
% endfor
<% propList = ', '.join([p['prop'] for p in props]) %>
% if propList:
    if (version < CLASS_VERSION_WITH_NVP)
    {
        a(${propList});
    }
    else
    {
    % for p in props:
        try
        {
            a(CEREAL_NVP(${p['prop']}));
        }
        catch (const cereal::Exception& e)
        {
            lg2::info("Could not restore property ${p['prop']} on ${object}, setting to default value");
            ${p['prop']} = ${get_default_value(object, p['iface'], p['prop'])};
        }
    % endfor
    }
% endif
<% props = [] %>
% for index, item in enumerate(settingsDict[object]):
  % for  prop, metaDict in item['Properties'].items():
<%
    t = "setting." + NamedElement(name=prop).camelCase + "(" + prop + ")"
%>\
    ${t};
  % endfor
% endfor
}

% for n in reversed(ns):
} // namespace ${n}
% endfor

% endfor

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
        explicit Manager(sdbusplus::bus_t& bus) :
            settings(
                std::make_tuple(
% for index, path in enumerate(objects):
<% type = get_setting_type(path) + "::Impl" %>\
                    std::make_unique<${type}>(
                        bus,
  % if index < len(settingsDict) - 1:
                        "${path}"),
  % else:
                        "${path}")
  % endif
% endfor
                )
            )
        {
% for index, path in enumerate(objects):
            auto initSetting${index} = [&]()
            {
  % for item in settingsDict[path]:
    % for propName, metaDict in item['Properties'].items():
<% p = NamedElement(name=propName).camelCase %>\
<% defaultValue = get_default_value(path, item['Interface'], propName) %>\
                std::get<${index}>(settings)->
                  ${get_setting_sdbusplus_type(item['Interface'])}::${p}(${defaultValue});
  % endfor
% endfor
            };

            try
            {
                if (std::get<${index}>(settings)->deserialize())
                {
                    /* Update the archive to use name/value pairs if it isn't. */
                    if (std::get<${index}>(settings)->getInitialVersion() < CLASS_VERSION_WITH_NVP)
                    {
                        std::get<${index}>(settings)->serialize();
                    }
                }
                else
                {
                    initSetting${index}();
                }
            }
            catch (const cereal::Exception& e)
            {
                lg2::error("Cereal exception on ${path}: {ERROR}", "ERROR", e);
                std::get<${index}>(settings)->removeFile();
                initSetting${index}();
            }
            std::get<${index}>(settings)->emit_object_added();

% endfor
        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
% for index, path in enumerate(objects):
<% type = get_setting_type(path) + "::Impl" %>\
  % if index < len(settingsDict) - 1:
            std::unique_ptr<${type}>,
  % else:
            std::unique_ptr<${type}>> settings;
  % endif
% endfor
};

} // namespace settings
} // namespace phosphor

// Now register the class version with Cereal
% for object in objects:
<%
   classname = "phosphor::settings"
   ns = object.split('/')
   ns.pop(0)
%>\
% for n in ns:
<%
    classname += "::" + n
%>\
% endfor
CEREAL_CLASS_VERSION(${classname + "::Impl"}, CLASS_VERSION);
% endfor
