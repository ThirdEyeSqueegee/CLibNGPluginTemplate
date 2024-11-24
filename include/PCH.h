#pragma once

/* +++++++++++++++++++++++++ C++23 Standard Library +++++++++++++++++++++++++ */

// C standard library headers
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

// C++ standard library headers
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
#include <coroutine>
#include <deque>
#include <exception>
#include <execution>
#include <expected>
#include <filesystem>
#include <format>
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
#include <list>
#include <locale>
#include <map>
#include <mdspan>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <print>
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
#include <spanstream>
#include <sstream>
#include <stack>
#include <stacktrace>
#include <stdexcept>
#include <stdfloat>
#include <stop_token>
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

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <REX/W32.h>
#include <SKSE/SKSE.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

using namespace std::literals;
using namespace REL::literals;

namespace logger = SKSE::log;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

template <typename TDerived, typename TEvent>
class EventHandler : public RE::BSTEventSink<TEvent>
{
protected:
    constexpr EventHandler() noexcept           = default;
    constexpr ~EventHandler() noexcept override = default;

public:
    constexpr EventHandler(const EventHandler&)   = delete;
    constexpr EventHandler(EventHandler&&)        = delete;
    constexpr auto operator=(const EventHandler&) = delete;
    constexpr auto operator=(EventHandler&&)      = delete;

    [[nodiscard]] static constexpr auto Get() noexcept
    {
        static TDerived handler;
        return std::addressof(handler);
    }

    static constexpr auto Register() noexcept
    {
        using TEventSource = RE::BSTEventSource<TEvent>;

        const std::string dirty_name{ typeid(TEvent).name() };
        const std::regex  p{ "class |struct |RE::|SKSE::| * __ptr64" };
        const auto        name{ std::regex_replace(dirty_name, p, "") };

        if constexpr (std::is_base_of_v<TEventSource, RE::BSInputDeviceManager>) {
            const auto manager{ RE::BSInputDeviceManager::GetSingleton() };
            manager->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        else if constexpr (std::is_base_of_v<TEventSource, RE::UI>) {
            const auto ui{ RE::UI::GetSingleton() };
            ui->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::ActionEvent>) {
            SKSE::GetActionEventSource()->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::CameraEvent>) {
            SKSE::GetCameraEventSource()->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::CrosshairRefEvent>) {
            SKSE::GetCrosshairRefEventSource()->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::ModCallbackEvent>) {
            SKSE::GetModCallbackEventSource()->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        else if constexpr (std::is_same_v<TEvent, SKSE::NiNodeUpdateEvent>) {
            SKSE::GetNiNodeUpdateEventSource()->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        else if constexpr (std::is_base_of_v<TEventSource, RE::ScriptEventSourceHolder>) {
            const auto holder{ RE::ScriptEventSourceHolder::GetSingleton() };
            holder->AddEventSink(Get());
            logger::info("Registered {} handler", name);
            logger::info("");
            return;
        }
        const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
        SKSE::stl::report_and_fail(std::format("{}: Failed to register {} handler", plugin->GetName(), name));
    }
};

namespace stl
{
    using namespace SKSE::stl;

    template <typename T, std::size_t Size = 5>
    constexpr auto write_thunk_call(REL::Relocation<> a_target) noexcept
    {
        T::func = a_target.write_call<Size>(T::Thunk);
    }

    template <typename T, std::size_t Size = 5>
    constexpr auto write_thunk_jump(REL::Relocation<> a_target) noexcept
    {
        T::func = a_target.write_branch<Size>(T::Thunk);
    }

    template <typename T>
    constexpr auto write_vfunc(const REL::VariantID variant_id) noexcept
    {
        REL::Relocation vtbl{ variant_id };
        T::func = vtbl.write_vfunc(T::idx, T::Thunk);
    }

    template <typename TDest, typename TSource>
    constexpr auto write_vfunc(const std::size_t a_vtableIdx = 0) noexcept
    {
        write_vfunc<TSource>(TDest::VTABLE[a_vtableIdx]);
    }

    namespace detail
    {
        template <typename>
        struct is_chrono_duration : std::false_type
        {};

        template <typename Rep, typename Period>
        struct is_chrono_duration<std::chrono::duration<Rep, Period>> : std::true_type
        {};

        template <typename T>
        concept is_duration = is_chrono_duration<T>::value;
    } // namespace detail

    auto add_thread_task(const std::function<void()>& a_fn, const detail::is_duration auto a_wait_for) noexcept
    {
        std::jthread{ [=] {
            std::this_thread::sleep_for(a_wait_for);
            SKSE::GetTaskInterface()->AddTask(a_fn);
        } }.detach();
    }
} // namespace stl
