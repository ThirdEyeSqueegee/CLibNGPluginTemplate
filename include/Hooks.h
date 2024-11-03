#pragma once

namespace Hooks
{
    void Install() noexcept;

    class MainUpdate
    {
    public:
        static i32 Thunk() noexcept;

        inline static REL::Relocation<decltype(&Thunk)> func;
    };
} // namespace Hooks
