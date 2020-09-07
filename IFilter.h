#pragma once
#include "opencv2/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <memory>
#include <string>
#include "defines.h"



class IFilter
{
public:
    typedef std::shared_ptr <IFilter> ptr;

    IFilter() {};
    virtual ~IFilter() {}

    virtual state_codes Init(const std::string& file_path) = 0;
    virtual state_codes Proceed() = 0;
    virtual cv::Mat GetObjectMat() = 0;
    virtual cv::Mat GetOriginMat() = 0;

protected:
    std::string m_filepath;

}; 

IFilter::ptr create_filter(filter_types type);
