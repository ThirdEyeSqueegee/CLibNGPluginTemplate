#include "Hooks.h"
#include "Events.h"
#include "Logging.h"
#include "SKSE/Interfaces.h"
#include "Settings.h"

void Listener(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        Settings::LoadSettings();
        Hooks::Install();
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLogging();

    const auto plugin = SKSE::PluginDeclaration::GetSingleton();
    const auto version = plugin->GetVersion();

    logger::info("{} {} is loading...", plugin->GetName(), version);

    Init(skse);

    if (const auto messaging = SKSE::GetMessagingInterface(); !messaging->RegisterListener(Listener))
        return false;

    logger::info("{} has finished loading.", plugin->GetName());

    return true;
}
