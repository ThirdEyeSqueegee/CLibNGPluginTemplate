#pragma once

#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/SKSE.h>
#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <charconv>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>
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
#include <ios>
#include <iosfwd>
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
#include <ratio>
#include <regex>
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
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

// clang-format off
#include <ShlObj_core.h>
#include <Psapi.h>
#include <Windows.h>
// clang-format on

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

using namespace std::literals;
using namespace REL::literals;

namespace logger = SKSE::log;

template <typename T>
class Singleton
{
protected:
    constexpr Singleton() noexcept  = default;
    constexpr ~Singleton() noexcept = default;

public:
    constexpr Singleton(const Singleton&)      = delete;
    constexpr Singleton(Singleton&&)           = delete;
    constexpr auto operator=(const Singleton&) = delete;
    constexpr auto operator=(Singleton&&)      = delete;

    static constexpr T* GetSingleton() noexcept
    {
        static T singleton;
        return std::addressof(singleton);
    }
};

template <typename TDerived, typename TEvent>
class EventSingleton : public RE::BSTEventSink<TEvent>
{
protected:
    constexpr EventSingleton() noexcept           = default;
    constexpr ~EventSingleton() noexcept override = default;

public:
    constexpr EventSingleton(const EventSingleton&) = delete;
    constexpr EventSingleton(EventSingleton&&)      = delete;
    constexpr auto operator=(const EventSingleton&) = delete;
    constexpr auto operator=(EventSingleton&&)      = delete;

    static constexpr TDerived* GetSingleton() noexcept
    {
        static TDerived singleton;
        return std::addressof(singleton);
    }

    static constexpr void Register() noexcept
    {
        using TEventSource = RE::BSTEventSource<TEvent>;

        constexpr std::string dirty_name{ typeid(TEvent).name() };
        const std::regex      p{ "struct |RE::|SKSE::| * __ptr64" };
        const auto            name{ std::regex_replace(dirty_name, p, "") };

        if constexpr (std::is_base_of_v<TEventSource, RE::BSInputDeviceManager>)
        {
            const auto manager{ RE::BSInputDeviceManager::GetSingleton() };
            manager->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        else if constexpr (std::is_base_of_v<TEventSource, RE::UI>)
        {
            const auto ui{ RE::UI::GetSingleton() };
            ui->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::ActionEvent>)
        {
            SKSE::GetActionEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::CameraEvent>)
        {
            SKSE::GetCameraEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::CrosshairRefEvent>)
        {
            SKSE::GetCrosshairRefEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::ModCallbackEvent>)
        {
            SKSE::GetModCallbackEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::NiNodeUpdateEvent>)
        {
            SKSE::GetNiNodeUpdateEventSource()->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        else if constexpr (std::is_base_of_v<TEventSource, RE::ScriptEventSourceHolder>)
        {
            const auto holder{ RE::ScriptEventSourceHolder::GetSingleton() };
            holder->AddEventSink(GetSingleton());
            logger::info("Registered {} handler", name);
            return;
        }
        const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
        SKSE::stl::report_and_fail(fmt::format("{}: Failed to register {} handler", plugin->GetName(), name));
    }
};

namespace stl
{
    using namespace SKSE::stl;

    template <typename T>
    constexpr void write_thunk_call() noexcept
    {
        SKSE::AllocTrampoline(14);
        auto& trampoline{ SKSE::GetTrampoline() };
        T::func = trampoline.write_call<5>(T::address, T::Thunk);
    }

    template <typename TDest, typename TSource>
    constexpr void write_vfunc() noexcept
    {
        REL::Relocation<std::uintptr_t> vtbl{ TDest::VTABLE[0] };
        TSource::func = vtbl.write_vfunc(TSource::idx, TSource::Thunk);
    }

    template <typename T>
    constexpr void write_vfunc(const REL::VariantID variant_id) noexcept
    {
        REL::Relocation<std::uintptr_t> vtbl{ variant_id };
        T::func = vtbl.write_vfunc(T::idx, T::Thunk);
    }
} // namespace stl
