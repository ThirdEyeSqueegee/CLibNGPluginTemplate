#pragma once

class Utility : public Singleton {
    using Singleton::Singleton;
    using Singleton::operator=;

public:
    static Utility* GetSingleton() {
        static Utility singleton;
        return std::addressof(singleton);
    }
};
