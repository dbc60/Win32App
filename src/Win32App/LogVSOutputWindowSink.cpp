/** ==========================================================================
* 2017 by Doug Cuthbertson, and adapted from the public domain code written by
* 2015 by KjellKod.cc
*
* This code is PUBLIC DOMAIN to use at your own risk and comes
* with no warranties. This code is yours to share, use and modify with no
* strings attached and no restrictions or obligations.
* ============================================================================*
* PUBLIC DOMAIN and Not copywrited. First published at KjellKod.cc
* ********************************************* */

#include "Win32AppConfig.h"
#include "g3sinks/LogVSOutputHelper.h"
#include "LogVSOutputWindowSink.h"
#include <g3log/std2_make_unique.hpp>
#include <algorithm>
#include <iostream> // to remove
#include <Windows.h>


/// @param log_prefix to use for the file
LogVSOutputWindowSink::LogVSOutputWindowSink(const std::string& log_prefix,
                                             const std::string& log_directory)
    : pimpl_(new LogVSOutputHelper(log_prefix, log_directory))
    , filter_{Logger::trace, Logger::debug}
{
}


LogVSOutputWindowSink::LogVSOutputWindowSink(const std::string& log_prefix,
                                             const std::string& log_directory,
                                             std::vector<LEVELS> filter)
    : pimpl_(new LogVSOutputHelper(log_prefix, log_directory))
    , filter_(filter) {
}


LogVSOutputWindowSink::~LogVSOutputWindowSink() {
}


/// @param logEntry to write to file
void LogVSOutputWindowSink::save(g3::LogMessageMover logEntry) {
    auto level = logEntry.get()._level;
    bool is_not_in_filter;
    
    {
        std::lock_guard<std::mutex> lock(mutex_filter_);
        is_not_in_filter = (filter_.end() == std::find(filter_.cbegin(), filter_.cend(), level));
    }

    if (is_not_in_filter) {
        pimpl_->fileWrite(logEntry.get().toString());
    }
}


/**
* Flush policy: Default is every single time (i.e. policy of 1).
*
* If the system logs A LOT then it is likely better to allow for the system to buffer and write
* all the entries at once.
*
* 0: System decides, potentially very long time
* 1....N: Flush logs every n entry
*/
void LogVSOutputWindowSink::setFlushPolicy(size_t flush_policy) {
    pimpl_->setFlushPolicy(flush_policy);
}

/**
* Force flush of log entries. This should normally be policed with the @ref setFlushPolicy
* but is great for unit testing and if there are special circumstances where you want to see
* the logs faster than the flush_policy
*/
void LogVSOutputWindowSink::flush() {
    pimpl_->flush();
}


void LogVSOutputWindowSink::setLogFilter(std::vector<LEVELS> filter) {
    std::lock_guard<std::mutex> lock(mutex_filter_);
    filter_.clear();
    filter_ = filter;
}
