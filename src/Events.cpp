#include "Events.h"

namespace Events {
    OnEquipEventHandler* OnEquipEventHandler::GetSingleton() {
        static OnEquipEventHandler singleton;
        return std::addressof(singleton);
    }

    RE::BSEventNotifyControl OnEquipEventHandler::ProcessEvent(const RE::TESEquipEvent* a_event,
                                                               RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) {
        if (!a_event)
            return RE::BSEventNotifyControl::kContinue;

        if (!a_event->equipped)
            return RE::BSEventNotifyControl::kContinue;

        // Do stuff

        return RE::BSEventNotifyControl::kContinue;
    }

    void OnEquipEventHandler::Register() {
        const auto holder = RE::ScriptEventSourceHolder::GetSingleton();
        holder->AddEventSink(GetSingleton());
        logger::info("Registered equip event handler");
    }
}
