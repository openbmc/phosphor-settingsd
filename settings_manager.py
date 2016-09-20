#!/usr/bin/python -u

import gobject
import dbus
import dbus.service
import dbus.mainloop.glib
import os
import os.path as path
import sys
from obmc.dbuslib.bindings import DbusProperties, get_dbus

settings_file_path = os.path.join(sys.prefix, 'share/obmc-phosphor-settings')
sys.path.insert(1, settings_file_path)
import settings_file as s
import re

DBUS_NAME = 'org.openbmc.settings.Host'
OBJ_NAME = '/org/openbmc/settings/host0'
CONTROL_INTF = 'org.openbmc.Settings'


class HostSettingsObject(DbusProperties):
    def __init__(self, bus, name, settings, path):
        super(HostSettingsObject, self).__init__(validator=self.input_validator, path=name)
        dbus.service.Object.__init__(self, bus, name)
        self.bus = bus
        self.path = path
        if not os.path.exists(path):
            os.mkdir(path)

        # Listen to changes in the property values and sync them to the BMC
        bus.add_signal_receiver(
            self.settings_signal_handler,
            dbus_interface="org.freedesktop.DBus.Properties",
            signal_name="PropertiesChanged",
            path="/org/openbmc/settings/host0")

        # Create the dbus properties
        for i in settings[DBUS_NAME].iterkeys():
            shk = settings[DBUS_NAME][i]
            self.set_settings_property(shk['name'],
                                       shk['type'],
                                       shk['default'])

    def get_bmc_value(self, name):
        try:
            with open(path.join(self.path, name), 'r') as f:
                return f.read()
        except (IOError):
            pass
        return None

    # Create dbus properties based on bmc value.
    # This will be either a value previously set,
    # or the default file value if the BMC value
    # does not exist.
    def set_settings_property(self, name, type, value):
        bmcv = self.get_bmc_value(name)
        if bmcv:
            value = bmcv
        if type == "i":
            self.Set(DBUS_NAME, name, int(value))
        elif type == "s":
            self.Set(DBUS_NAME, name, str(value))
        elif type == "b":
            self.Set(DBUS_NAME, name, int(value))

    # Save the settings to the BMC. This will write the settings value in
    # individual files named by the property name to the BMC.
    def set_system_settings(self, name, value):
        bmcv = self.get_bmc_value(name)
        if bmcv != value:
            filepath = path.join(self.path, name)
            with open(filepath, 'w') as f:
                f.write(str(value))

    # Signal handler for when one ore more settings properties were updated.
    # This will sync the changes to the BMC.
    def settings_signal_handler(
            self, interface_name, changed_properties, invalidated_properties):
        for name, value in changed_properties.items():
            self.set_system_settings(name, value)

    # Placeholder signal. Needed to register the settings interface.
    @dbus.service.signal(DBUS_NAME, signature='s')
    def SettingsUpdated(self, sname):
        pass

    # Validates the input matching a regular expression
    def validate_regex(self, regex, value):
        if not re.compile(regex).search(value):
            raise ValueError, "Invalid input"

    # Validates the input matching a range
    def validate_range(self, min, max, value):
        if value not in range(min, max):
            raise ValueEror, "Invalid input"

    # Validates the input matching a pre defined list
    def validate_list(self, list, value):
        if value not in list:
            raise ValueEror, "Invalid input"

    # Offloading the validation to plugins for complex inputs
    def validate_plugin(self, busname, objpath, intf, method, value):
        plugin = self.bus.get_object(busname, objpath)
	plugin_method = plugin.get_dbus_method(method, intf)
	plugin_method()

    def input_validator(self, iface, property, value):
	settings = s.SETTINGS
        # Validate to see if the changes are in order
        # TODO when this changes to multiple levels, need to make a change here.
        # Idea is to use self.path and enter into needed section
        for i in settings[iface].iterkeys():
            shk = settings[iface][i]
	    if shk['name'] == property:
                if shk['validation'] == 'list':
                    self.validate_list(shk['allowed'], value)

                elif shk['validation'] == 'range':
		    self.validate_range(shk['min'], shk['max']+1, value)

		elif shk['validation'] == 'regex':
		    self.validate_regex(shk['regex'], value)

		elif shk['validation'] == 'plugin':
		    self.validate_plugin(shk['service'], shk['obj'], \
                            shk['intf'], shk['method'], value)

                # We have processed the input.
                break

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    bus = get_dbus()
    obj = HostSettingsObject(bus, OBJ_NAME, s.SETTINGS, "/var/lib/obmc/")
    mainloop = gobject.MainLoop()

    obj.unmask_signals()
    name = dbus.service.BusName(DBUS_NAME, bus)
    print "Running HostSettingsService"
    mainloop.run()
