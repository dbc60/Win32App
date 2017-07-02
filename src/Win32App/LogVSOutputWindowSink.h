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
    using IgnoreLogLevelsFilter = std::vector<LEVELS>;

    // Forward log LEVELS that are not in the filter
    IgnoreLogLevelsFilter               filter_;
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


    void setMaxLogSize(int max_file_size_in_bytes);
};
