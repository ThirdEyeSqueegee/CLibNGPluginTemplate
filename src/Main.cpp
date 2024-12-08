#include "Events.h"
#include "Hooks.h"
#include "Settings.h"

void Listener(SKSE::MessagingInterface::Message* message) noexcept
{
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        Settings::LoadSettings();
        Events::EquipEventHandler::Register();
        Hooks::Install();
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    Init(skse);

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto name{ plugin->GetName() };
    const auto version{ plugin->GetVersion() };

    logger::init();

    logger::info("{} {} is loading...", name, version);

    // The following is only required if you use write_thunk_call or write_thunk_jump. If you aren't using
    // those function, you can safely remove this line.
    //
    // To calculate the size of the trampoline, take the number of 5 byte write_call/write_branch, say p,
    // and the number of 6 byte write_call/write_branch, say q. Then, the size of the trampoline is given
    // by (p * 14) + (q * 8). E.g.: If you have two 5 byte write_calls and one 6 byte write_branch, the size
    // of the trampoline should be (2 * 14) + (1 * 8) = 34.
    SKSE::AllocTrampoline(14);

    if (const auto messaging{ SKSE::GetMessagingInterface() }; !messaging->RegisterListener(Listener)) {
        return false;
    }

    logger::info("{} has finished loading.", name);
    logger::info("");

    return true;
}
