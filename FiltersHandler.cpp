#include "FiltersHandler.h"
#include "IFilter.h"
#include "Logger.h"

void DrawDebug(cv::Mat img)
{
    cv::namedWindow("test", 1);
    cv::imshow("test", img);
    cv::waitKey();
}

FiltersHandler::FiltersHandler()
    :m_stopped(true)
{
    LOG_DBG("FiltersHandler::FiltersHandler");
}

FiltersHandler::~FiltersHandler()
{
}

void FiltersHandler::Init(const std::string& image_path)
{
    LOG_DBG("FiltersHandler::Init");
    m_image_path = image_path;
}

void FiltersHandler::SetLogger(std::shared_ptr<FileLogger> logger)
{
    m_logger = logger;
}

bool FiltersHandler::Stopped()
{
    LOG_DBG("FiltersHandler::Stopped");
    return m_stopped;
}

state_codes FiltersHandler::Start()
{
    LOG_DBG("FiltersHandler::Start");
    
    state_codes result = state_codes::STATE_SUCCEDED;
    m_stopped = false;

    m_filters.push_back(create_filter(filter_types::ball));
    
    for (const IFilter::ptr& f : m_filters)
    {
        if (f->Init(m_image_path) == (result = state_codes::CLASSIFIER_LOAD_FAIL))
        {
            m_stopped = true;
            return result;
        }

        if(f->Proceed() != (result = state_codes::STATE_SUCCEDED))
            break;

        DrawDebug(f->GetObjectMat());
        DrawDebug(f->GetOriginMat());


    }

    m_stopped = true;
    return result;
}


