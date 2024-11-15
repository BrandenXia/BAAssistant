#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Baa {

void initLog() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::trace);
#else
    spdlog::set_level(spdlog::level::info);
#endif

    auto logger = spdlog::stdout_color_mt("BAA");
    spdlog::set_default_logger(logger);
}

}