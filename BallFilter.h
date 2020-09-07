#pragma once
#include "IFilter.h"
#include "defines.h"

class BallFilter : public IFilter
{
public:
    BallFilter();
    ~BallFilter();

public:
    state_codes Init(const std::string& file_path);
    state_codes Proceed();
    cv::Mat GetObjectMat();
    cv::Mat GetOriginMat();

private:
    bool CropBall(cv::Mat img, const std::vector<cv::Rect>& balls);
    bool DetectBall();


private:
    cv::Rect m_cropedROI;
    cv::Mat m_originMat;
    cv::Mat m_croppedBallMat;
    std::string m_image_path;
    cv::CascadeClassifier m_ball_cascade;
    
};
