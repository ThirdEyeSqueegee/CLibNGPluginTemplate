#include "Events.h"

namespace Events
{
    RE::BSEventNotifyControl OnEquipEventHandler::ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource)
    {
        if (!a_event)
            return RE::BSEventNotifyControl::kContinue;

        // Do stuff

        return RE::BSEventNotifyControl::kContinue;
    }
} // namespace Events
