#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Baa {

void initLog() {
    spdlog::set_level(
#ifdef DEBUG
        spdlog::level::trace
#else
        spdlog::level::info
#endif
    );
    spdlog::set_pattern(
#ifdef DEBUG
        "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%s:%#] %v"
#else
        "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v"
#endif
    );

    auto logger = spdlog::stdout_color_mt("BAA");
    spdlog::set_default_logger(logger);
}

}