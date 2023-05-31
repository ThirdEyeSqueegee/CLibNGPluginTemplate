#include "Logging.h"
#include "SKSE/Interfaces.h"
#include "Events.h"

void Listener(SKSE::MessagingInterface::Message* message) {
    // Initialize listener
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLogging();
    const auto* plugin = SKSE::PluginDeclaration::GetSingleton();
    auto version = plugin->GetVersion();
    SKSE::log::info("{} {} is loading...", plugin->GetName(), version);
    Init(skse);

    const auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener(Listener)) return false;

    SKSE::log::info("{} has finished loading.", plugin->GetName());
    return true;
}
