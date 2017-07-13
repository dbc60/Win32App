/* ========================================================================
Author: Douglas B. Cuthbertson
(C) Copyright 2017 by Douglas B. Cuthbertson. All Rights Reserved.
======================================================================== */
#include "LoggerG3LogT.h"
#include "Win32AppConfig.h"

enum LogLevels {
    LL_TRACE = g3::kDebugValue - 10,
    LL_DEBUG = g3::kDebugValue,
    LL_VERBOSE = g3::kDebugValue + 10,
    LL_INFO = g3::kInfoValue,
    LL_WARNING = g3::kWarningValue,
    LL_ERROR = g3::kWarningValue + 10,
    LL_FATAL = g3::kFatalValue,
    LL_UNKNOWN = g3::kFatalValue + 10
};

const LEVELS Logger::trace = {LL_TRACE, "trace"};
const LEVELS Logger::debug = {LL_DEBUG, "debug"};
const LEVELS Logger::verbose = {LL_VERBOSE, "verbose"};
const LEVELS Logger::info = {LL_INFO, "info"};
const LEVELS Logger::warning = {LL_WARNING, "warning"};
const LEVELS Logger::error = {LL_ERROR, "error"};
const LEVELS Logger::fatal = {LL_FATAL, "fatal"};

std::unique_ptr<g3::SinkHandle<LogSink>> Logger::sink_;

Logger::LoggerG3LogT() {
}


void
Logger::initLogging(const char* log_prefix,
                    const char* log_path) {
    static std::unique_ptr<g3::LogWorker> worker{g3::LogWorker::createLogWorker()};
    sink_ = std::move(worker->addSink(std::make_unique<LogSink>(log_prefix, log_path),
                            &LogSink::save));

    // Initialize the logger so it can receive LOG calls
    g3::initializeLogging(worker.get());
    //std::future<void> received = sink->call(&LogSink::setMaxLogSize,
    //                                        static_cast<int>(MEGABYTES(10)));
}


u32
Logger::StringToLogLevel(const std::string& log_level) {
    u32 result;
    std::string test;

    // Make sure the input string is in lowercase
    for (auto itr : log_level) {
        test += ::tolower(itr);
    }

    if (test == Logger::trace.text) {
        result = LL_TRACE;
    } else if (test == Logger::debug.text) {
        result = LL_DEBUG;
    } else if (test == Logger::verbose.text) {
        result = LL_VERBOSE;
    } else if (test == Logger::info.text) {
        result = LL_INFO;
    } else if (test == Logger::warning.text) {
        result = LL_WARNING;
    } else if (test == Logger::error.text) {
        result = LL_ERROR;
    } else if (test == Logger::fatal.text) {
        result = LL_FATAL;
    } else {
        result = LL_UNKNOWN;
    }

    return result;
}


std::string
Logger::LogLevelToString(u32 ll) {
    std::string result;

    switch (ll) {
    case LL_TRACE:
        result = "trace";
        break;

    case LL_DEBUG:
        result = "debug";
        break;

    case LL_VERBOSE:
        result = "verbose";
        break;

    case LL_INFO:
        result = "info";
        break;

    case LL_WARNING:
        result = "warning";
        break;

    case LL_ERROR:
        result = "error";
        break;

    case LL_FATAL:
        result = "fatal";
        break;

    default:
        result = "unknown";
        break;
    }

    return result;
}


void
Logger::setLogFilter(std::vector<LEVELS> filter) {
    // Give the consumer thread a chance to empty the queue
    std::this_thread::yield();
    std::future<void> received = sink_->call(&LogSink::setLogFilter, filter);
}