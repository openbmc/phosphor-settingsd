## Introduction

The settings manager has the following design goals:

* Each setting should be a distinct d-bus object.

* The above makes it possible to not even create settings objects that do not
  apply to a specific system.

* It should be possible, for example, for host0/ and host1/ on a system with
  two hosts to not only have different values for certain settings, but
  have different applicable settings as well.

* It should be possible to specify default settings for a system at build-time,
  based on which the settings manager should at run-time create appopriate
  d-bus objects and place them on the bus.

## Settings policy file

Some of the design goals above are achieved via a policy file, which is written
in YAML. Based on this policy file, the settings manager code is generated to be
able to create only relevant settings d-bus objects along with specifying their
defaults.

Here's an example of how entries in the YAML would look:

```
/xyz/openbmc_project/settings/host0/boot_mode:
    Interface: xyz.openbmc_project.Settings.Boot.Mode
    Defaults:
        BootMode: boot::Mode::Modes::Regular

/xyz/openbmc_project/settings/host1/boot_mode:
    Interface: xyz.openbmc_project.Settings.Boot.Mode
    Defaults:
        BootMode: boot::Mode::Modes::Safe
```

It is possible to specify this policy file via a bitbake recipe for a system
specific policy.
