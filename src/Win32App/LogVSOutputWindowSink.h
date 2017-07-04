#pragma once


#include "g3log\loglevels.hpp"
#include <string>
#include <memory>
#include <vector>


struct LogVSOutputHelper;

/**
* \param log_prefix is the 'name' of the binary, this give the log name 'LOG-'name'-...
* \param log_directory gives the directory to put the log files */
class LogVSOutputWindowSink {
public:
    using IgnoreLogLevelsFilter = std::vector<LEVELS>;

private:
    // Forward log LEVELS that are not in the filter
    IgnoreLogLevelsFilter               filter_;
    std::mutex                          mutex_filter_;
    std::unique_ptr<LogVSOutputHelper>  pimpl_;

public:
    LogVSOutputWindowSink(const LogVSOutputWindowSink&) = delete;
    LogVSOutputWindowSink& operator=(const LogVSOutputWindowSink&) = delete;

    LogVSOutputWindowSink(const std::string& log_prefix,
                          const std::string& log_directory);

    LogVSOutputWindowSink(const std::string& log_prefix,
                          const std::string& log_directory,
                          std::vector<LEVELS> filter);

    virtual ~LogVSOutputWindowSink();

    void save(g3::LogMessageMover logEnty);

    // 0: never (system auto flush), 1 ... N: every n times
    void setFlushPolicy(size_t flush_policy);
    void flush();

    void setLogFilter(std::vector<LEVELS> filter);
};
