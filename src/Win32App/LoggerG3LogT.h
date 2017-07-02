#pragma once

#include "platform.h"
#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"
#include "g3log/std2_make_unique.hpp"
#include <iomanip>

template <typename Config_>
class LoggerG3LogT {
public:
    // Configuration
    typedef Config_                     Config;
    typedef typename Config::LogSink    LogSink;

    static const LEVELS trace;
    static const LEVELS debug;
    static const LEVELS verbose;
    static const LEVELS info;
    static const LEVELS warning;
    static const LEVELS error;
    static const LEVELS fatal;

    LoggerG3LogT();
    static void initLogging(const char* log_prefix, const char* log_path);
    static u32 StringToLogLevel(const std::string& log_level);
    static std::string LogLevelToString(u32 ll);
};
