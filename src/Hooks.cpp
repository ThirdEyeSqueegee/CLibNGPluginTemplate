#include "Hooks.h"

namespace Hooks
{
    void Install() noexcept
    {
        REL::Relocation main_update{ RELOCATION_ID(35565, 36564), REL::Relocate(0x748, 0xc26, 0x7ee) };
        stl::write_thunk_call<MainUpdate>(main_update);
        logger::info("Installed main update hook");
        logger::info("");
    }

    i32 MainUpdate::Thunk() noexcept { return func(); }
} // namespace Hooks
