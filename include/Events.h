#pragma once

namespace Events {
    class OnEquipEventHandler : public RE::BSTEventSink<RE::TESEquipEvent> {
    protected:
        OnEquipEventHandler() = default;
        ~OnEquipEventHandler() override = default;

    public:
        OnEquipEventHandler(const OnEquipEventHandler&) = delete;
        OnEquipEventHandler(OnEquipEventHandler&&) = delete;
        OnEquipEventHandler& operator=(const OnEquipEventHandler&) = delete;
        OnEquipEventHandler& operator=(OnEquipEventHandler&&) = delete;

        static OnEquipEventHandler* GetSingleton();

        RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;

        static void Register();
    };
}
