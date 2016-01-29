#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <systemd/sd-bus.h>

const char *gService = "org.openbmc.settings.Host";
const char *gObjPath = "/org/openbmc/settings/host0";
const char *gIntPath = "org.openbmc.Settings";


typedef struct _settings_t {
    char*   currentBootMode;
    int32_t powercap;
    int32_t powercap_min;
    int32_t powercap_max;
    int32_t powercap_default;
} settings_t;

#define MAX_BOOT_MODES 6
char gPossibleBootModes[MAX_BOOT_MODES][10] = {
    "Default",
    "Network",
    "Disk",
    "Safe",
    "CDROM",
    "Setup"
};

static int method_boot_mode_list(sd_bus *bus,
                          const char *path,
                          const char *interface,
                          const char *property,
                          sd_bus_message *reply,
                          void *userdata,
                          sd_bus_error *error) {

    int r, i=0;

    printf("Building boot mode list\n");

    r = sd_bus_message_open_container(reply, 'a', "s");
    if (r < 0)
        return r;

    for (i=0;i<MAX_BOOT_MODES;i++) {
        r = sd_bus_message_append(reply, "s", gPossibleBootModes[i]);
        if (r < 0) {
            fprintf(stderr, "Failed to build the list of failed boot modes: %s", strerror(-r));
            return r;
        }
    }

    return sd_bus_message_close_container(reply);
}

static int method_setBootMode(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    int i, r=-1;
    char *str;
    settings_t *settings = (settings_t *) userdata;

    printf("Setting boot mode list\n");

    r = sd_bus_message_read(m, "s", &str);
    if (r < 0) {
        fprintf(stderr, "Failed to extract string: %s", strerror(-r));
        goto final;
    } 

    for (i=0;i<MAX_BOOT_MODES;i++) {
        if(!strcmp(gPossibleBootModes[i], str)) {
            settings->currentBootMode = &gPossibleBootModes[i][0];
            break;
        }
    }

    if (i == MAX_BOOT_MODES) {
        // Getting here means string of what 
        // they wanted did not map to anything
        r = -1;
    }

    final:
    return sd_bus_reply_method_return(m, "i", r);
}


static int method_setPowerCap(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    int r;
    int32_t  pcap;
    settings_t *settings = (settings_t *) userdata;

    printf("Setting Power Cap\n");

    r = sd_bus_message_read(m, "i", &pcap);
    if (r < 0) {
        fprintf(stderr, "Failed to extract data: %s", strerror(-r));
    }  else {

        if ((pcap <= settings->powercap_max) &&
            (pcap >= settings->powercap_min)) {
                settings->powercap = pcap;
        } else {
            return sd_bus_reply_method_error(m,&SD_BUS_ERROR_MAKE_CONST( \
                SD_BUS_ERROR_INVALID_ARGS,                               \
                "value not supported"));
        }
    }

    return sd_bus_reply_method_return(m, "i", r);
}

static const sd_bus_vtable vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD("setBootMode", "s", "i", method_setBootMode, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_METHOD("setPowerCap", "i", "i", method_setPowerCap, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_PROPERTY("current_boot_mode", "s", NULL, offsetof(settings_t, currentBootMode), SD_BUS_VTABLE_PROPERTY_CONST),
    SD_BUS_PROPERTY("boot_mode_list", "as", method_boot_mode_list, 0, SD_BUS_VTABLE_PROPERTY_CONST),
    SD_BUS_PROPERTY("power_cap_now",     "i", NULL, offsetof(settings_t, powercap), SD_BUS_VTABLE_PROPERTY_CONST),
    SD_BUS_PROPERTY("power_cap_min",     "i", NULL, offsetof(settings_t, powercap_min), SD_BUS_VTABLE_PROPERTY_CONST),
    SD_BUS_PROPERTY("power_cap_max",     "i", NULL, offsetof(settings_t, powercap_max), SD_BUS_VTABLE_PROPERTY_CONST),
    SD_BUS_PROPERTY("power_cap_default", "i", NULL, offsetof(settings_t, powercap_default), SD_BUS_VTABLE_PROPERTY_CONST),
    SD_BUS_VTABLE_END
};


void init_settings(settings_t *p) {

    // Someday there will be a file that the defaults can come from
    // This stuff for now is completely fake and doesn't do anything.
    // Simply the place holder to make it easier for the pcap to be
    // set
    settings_t t = { 
        gPossibleBootModes[0],
        998, 1, 1000, 999
    };

    memcpy(p,&t,sizeof(settings_t));

    return;
}

int start_HostSettingsService(void) {

    sd_bus *bus;
    sd_bus_slot *slot;
    int r;
    settings_t settings;

    init_settings(&settings);

    r = sd_bus_open_system(&bus);
    if (r < 0) {
        fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
        goto finish;
    }

    /* Install the object */
    r = sd_bus_add_object_vtable(bus,
                                 &slot,
                                 gObjPath,
                                 gIntPath,
                                 vtable,
                                 &settings);
    if (r < 0) {
        fprintf(stderr, "Failed to issue method call: %s\n", strerror(-r));
        goto finish;
    }
    
    /* Take a well-known service name so that clients can find us */
    r = sd_bus_request_name(bus, gService, 0);
    if (r < 0) {
        fprintf(stderr, "Failed to acquire service name: %s\n", strerror(-r));
        goto finish;
    }


    for (;;) {
        r = sd_bus_process(bus, NULL);
        if (r < 0) {
            fprintf(stderr, "Failed to process bus: %s\n", strerror(-r));
            goto finish;
        }

        if (r > 0)
            continue;       

        r = sd_bus_wait(bus, (uint64_t) -1);
        if (r < 0) {
            fprintf(stderr, "Failed to wait on bus: %s\n", strerror(-r));
            goto finish;
        }
    }
    finish:
        sd_bus_unref(bus);

    return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {

    return start_HostSettingsService();
}