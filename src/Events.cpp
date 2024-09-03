#include "Events.h"

namespace Events
{
    RE::BSEventNotifyControl EquipEventHandler::ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) noexcept
    {
        if (!a_event) {
            return RE::BSEventNotifyControl::kContinue;
        }

        // Do stuff

        return RE::BSEventNotifyControl::kContinue;
    }
} // namespace Events
