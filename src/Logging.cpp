#include "Logging.h"

void InitializeLogging() noexcept
{
    auto path{ SKSE::log::log_directory() };
    if (!path) {
        stl::report_and_fail("Unable to lookup SKSE logs directory.");
    }
    *path /= SKSE::PluginDeclaration::GetSingleton()->GetName();
    *path += L".log";

    std::shared_ptr<spdlog::logger> log;
    if (IsDebuggerPresent()) {
        log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
    }
    else {
        log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
    }

    log->set_level(spdlog::level::info);
    log->flush_on(spdlog::level::trace);

    set_default_logger(std::move(log));

    spdlog::set_pattern("[%T.%e UTC%z] [%L] [%=5t] %v");
}
