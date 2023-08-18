#pragma once

namespace Events {
    class OnEquipEventHandler : public EventSingleton<OnEquipEventHandler, RE::TESEquipEvent> {
    public:
        RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;
    };
}
