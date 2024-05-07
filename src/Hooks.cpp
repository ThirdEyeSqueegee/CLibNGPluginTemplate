#include "Hooks.h"

namespace Hooks
{
    void Install() noexcept
    {
        stl::write_thunk_call<MainUpdate>();
        logger::info("Installed main update hook");
    }

    std::int32_t MainUpdate::Thunk() noexcept
    {
        return func();
    }
} // namespace Hooks
