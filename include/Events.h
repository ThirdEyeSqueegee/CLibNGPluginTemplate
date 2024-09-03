#pragma once

namespace Events
{
    class EquipEventHandler : public EventSingleton<EquipEventHandler, RE::TESEquipEvent>
    {
    public:
        RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) noexcept override;
    };
} // namespace Events
