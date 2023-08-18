#pragma once

class Settings : public Singleton {
    using Singleton::Singleton;
    using Singleton::operator=;

public:
    static Settings* GetSingleton();

    static void LoadSettings();

    inline static bool debug_logging = false;
};
