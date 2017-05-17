## This file is a template.  The comment below is emitted
## into the rendered file; feel free to edit this file.
// WARNING: Generated header. Do not edit!

<%
objects = list(settingsDict.viewkeys())

def get_setting_type(setting_intf):
    setting = setting_intf.replace('xyz.openbmc_project.Settings.', '')
    l = setting.split('.')
    setting = l[-1];
    l = l[:-1]
    if l:
        l = [item.lower() for item in l]
        namespaces = '::'.join(l)
        setting = namespaces + '::' + setting
    return setting
%>\
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
% for index, object in enumerate(objects):
<% type = get_setting_type(settingsDict[object]['Interface']) %>\
                    std::make_unique<${type}>(
                        bus,
  % if index < len(settingsDict) - 1:
                        "${object}"),
  % else:
                        "${object}"));
  % endif
% endfor

% for index, object in enumerate(objects):
  % if 'Defaults' in settingsDict[object].viewkeys():
    % for property, value in settingsDict[object]['Defaults'].items():
            std::get<${index}>(settings)->
                setPropertyByName("${property}", ${value});
    % endfor
  % endif
            std::get<${index}>(settings)->emit_object_added();

% endfor
        }

    private:
        /* @brief Composition of settings objects. */
        std::tuple<
% for index, object in enumerate(objects):
<% type = get_setting_type(settingsDict[object]['Interface']) %>\
  % if index < len(settingsDict) - 1:
            std::unique_ptr<${type}>,
  % else:
            std::unique_ptr<${type}>> settings;
  % endif
% endfor
};

} // namespace settings
} // namespace phosphor
