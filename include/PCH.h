#pragma once

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <iosfwd>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <ratio>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <REL/Relocation.h>

#include <ShlObj_core.h>
#include <Windows.h>
#include <Psapi.h>
#undef cdecl // Workaround for Clang 14 CMake configure error.

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

// Compatible declarations with other sample projects.
#define DLLEXPORT __declspec(dllexport)

using namespace std::literals;
using namespace REL::literals;

namespace logger = SKSE::log;

template <class T>
class Singleton {
protected:
    constexpr Singleton() = default;
    constexpr ~Singleton() = default;

public:
    constexpr Singleton(const Singleton&) = delete;
    constexpr Singleton(Singleton&&) = delete;
    constexpr auto operator=(const Singleton&) = delete;
    constexpr auto operator=(Singleton&&) = delete;

    static T* GetSingleton() {
        static T singleton;
        return std::addressof(singleton);
    }
};

template <class T, class E>
class EventSingleton : public RE::BSTEventSink<E> {
protected:
    constexpr EventSingleton() = default;
    constexpr ~EventSingleton() override = default;

public:
    constexpr EventSingleton(const EventSingleton&) = delete;
    constexpr EventSingleton(EventSingleton&&) = delete;
    constexpr auto operator=(const EventSingleton&) = delete;
    constexpr auto operator=(EventSingleton&&) = delete;

    static T* GetSingleton() {
        static T singleton;
        return std::addressof(singleton);
    }

    static void Register() {
        using eventsource_t = RE::BSTEventSource<E>;

        auto name = std::string(typeid(E).name());
        const std::regex p("struct |RE::|SKSE::| * __ptr64");
        name = std::regex_replace(name, p, "");

        if constexpr (std::is_base_of_v<eventsource_t, RE::BSInputDeviceManager>) {
            const auto manager = RE::BSInputDeviceManager::GetSingleton();
            manager->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        } else if constexpr (std::is_base_of_v<eventsource_t, RE::UI>) {
            const auto ui = RE::UI::GetSingleton();
            ui->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        } else if constexpr (std::is_same_v<E, SKSE::ActionEvent>) {
            SKSE::GetActionEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        } else if constexpr (std::is_same_v<E, SKSE::CameraEvent>) {
            SKSE::GetCameraEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        } else if constexpr (std::is_same_v<E, SKSE::CrosshairRefEvent>) {
            SKSE::GetCrosshairRefEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        } else if constexpr (std::is_same_v<E, SKSE::ModCallbackEvent>) {
            SKSE::GetModCallbackEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        } else if constexpr (std::is_same_v<E, SKSE::NiNodeUpdateEvent>) {
            SKSE::GetNiNodeUpdateEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        } else if constexpr (std::is_base_of_v<eventsource_t, RE::ScriptEventSourceHolder>) {
            const auto holder = RE::ScriptEventSourceHolder::GetSingleton();
            holder->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        const auto plugin = SKSE::PluginDeclaration::GetSingleton();
        SKSE::stl::report_and_fail(fmt::format("{}: Failed to register {} handler", plugin->GetName(), name));
    }
};

namespace stl {
    using namespace SKSE::stl;

    template <class T>
    void write_thunk_call() {
        SKSE::AllocTrampoline(14);
        auto& trampoline = SKSE::GetTrampoline();
        T::func = trampoline.write_call<5>(T::address, T::Thunk);
    }

    template <class S, class T>
    void write_vfunc() {
        REL::Relocation<std::uintptr_t> vtbl{ S::VTABLE[0] };
        T::func = vtbl.write_vfunc(T::idx, T::Thunk);
    }

    template <class T>
    void write_vfunc(const REL::VariantID variant_id) {
        REL::Relocation<std::uintptr_t> vtbl{ variant_id };
        T::func = vtbl.write_vfunc(T::idx, T::Thunk);
    }
}
