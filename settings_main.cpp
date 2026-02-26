#include "settings_manager.hpp"

#include <phosphor-logging/lg2.hpp>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/manager.hpp>
#include <sdeventplus/event.hpp>
#include <sdeventplus/source/signal.hpp>

#include <csignal>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    auto bus = sdbusplus::bus::new_default();

    // Add sdbusplus ObjectManager. The settings objects are spread across
    // the object namespace and are not under a (settings) root. Hence register
    // "/" as the path.
    sdbusplus::server::manager_t objManager(bus, "/");

    phosphor::settings::Manager mgr(bus);

    // Attach the D-Bus connection to sd-event loop.
    auto event = sdeventplus::Event::get_default();
    bus.attach_event(event.get(), SD_EVENT_PRIORITY_NORMAL);

    // Block SIGHUP so the kernel holds it as pending instead of applying the
    // default action.
    sigset_t ss;
    if (sigemptyset(&ss) < 0 || sigaddset(&ss, SIGHUP) < 0)
    {
        lg2::error("Failed to setup signal mask");
        return 1;
    }
    if (sigprocmask(SIG_BLOCK, &ss, nullptr) < 0)
    {
        lg2::error("Failed to block SIGHUP signal");
        return 1;
    }

    sdeventplus::source::Signal sighupHandler(
        event, SIGHUP,
        [&mgr](sdeventplus::source::Signal&, const struct signalfd_siginfo*) {
            lg2::info("Received SIGHUP signal, reloading settings");
            try
            {
                mgr.reloadAllSettings();
            }
            catch (const std::exception& e)
            {
                lg2::error("Failed to reload settings: {ERROR}", "ERROR", e);
            }
        });

    bus.request_name(SETTINGS_BUSNAME);

    // Run the event loop
    return event.loop();
}
