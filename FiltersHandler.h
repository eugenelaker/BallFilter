#pragma once

#include <memory>
#include <vector>
#include <string>
#include "IFilter.h"
#include "defines.h"

class FileLogger;

class FiltersHandler
{
public:
    FiltersHandler();
    ~FiltersHandler();

public:
    void Init(const std::string& image_path);
    state_codes Start();
    bool Stopped();
    void SetLogger(std::shared_ptr<FileLogger> logger);

private:
    bool m_stopped;
    std::string m_image_path;
    std::shared_ptr<FileLogger> m_logger;
    std::vector<IFilter::ptr> m_filters;

};