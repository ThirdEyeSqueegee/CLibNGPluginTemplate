#pragma once

class Settings
{
public:
    static void LoadSettings() noexcept;

    inline static bool debug_logging{};
};
