#pragma once

namespace Hooks
{
    void Install() noexcept;

    class MainUpdate : public Singleton<MainUpdate>
    {
    public:
        static std::int32_t Thunk() noexcept;

        inline static REL::Relocation<decltype(&Thunk)> func;

        inline static const REL::Relocation<std::uintptr_t> target{ REL::RelocationID(35565, 36564), REL::Relocate(0x748, 0xc26, 0x7ee) };

        inline static const auto address{ target.address() };
    };
} // namespace Hooks
