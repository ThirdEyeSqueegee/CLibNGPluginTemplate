#pragma once

namespace Events {
    class OnEquipEventHandler : public EventSingleton<RE::TESEquipEvent> {
        using EventSingleton::EventSingleton;
        using EventSingleton::operator=;

    public:
        static OnEquipEventHandler* GetSingleton();

        RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;

        static void Register();
    };
}
