#ifndef BAASSISTANT_LOG_H
#define BAASSISTANT_LOG_H

#ifdef DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include "spdlog/spdlog.h"

namespace Baa {
    void initLog();
}

#ifdef DEBUG
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#else
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#endif

#endif  // BAASSISTANT_LOG_H
