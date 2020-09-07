#include "BallFilter.h"
#include "Logger.h"
#include <iostream>
#include <string>

BallFilter::BallFilter()
{
    LOG_DBG("BallFilter::Constructor");
}

BallFilter::~BallFilter()
{
    LOG_DBG("BallFilter::Destructor");

    cv::destroyAllWindows();
}

state_codes BallFilter::Init(const std::string& file_path)
{
    LOG_DBG("BallFilter::Init");
   
    if (!m_ball_cascade.load(BALL_CLASSIFIER_XML))
    { 
        LOG_DBG("BallFilter::Init  Error loading ball cascade");
        return state_codes::CLASSIFIER_LOAD_FAIL;
    };

    m_image_path = file_path;
    
    return state_codes::STATE_SUCCEDED;
}

state_codes BallFilter::Proceed()
{
    LOG_DBG("BallFilter::Proceed");
    cv::Mat originMat, grayMat, workMat;
    if (!(m_originMat = cv::imread(m_image_path)).data)
    {
        LOG_DBG("BallFilter::Proceed -- Error loading image");
        return state_codes::STATE_ERROR_LOADING_IMAGE;
    }

    if (!DetectBall())
    {
        LOG_WRN("BallFilter::Proceed -- Ball not detected");
        return state_codes::OBJECT_NOT_DETECTED;
    }

    return state_codes::STATE_SUCCEDED;
}

cv::Mat BallFilter::GetObjectMat()
{
    return m_croppedBallMat;
}

cv::Mat BallFilter::GetOriginMat()
{
    return m_originMat;
}


bool BallFilter::CropBall(cv::Mat img, const std::vector<cv::Rect>& balls)
{
    LOG_DBG("BallFilter::CropBall");
    cv::Mat circleMat;

    cv::Mat mask = cv::Mat(img.rows, img.cols, img.type(), cv::Scalar(0));
    cv::Mat maskedCircle = cv::Mat(img.rows, img.cols, img.type(), cv::Scalar(0));
    cv::Mat dest = cv::Mat(img.rows, img.cols, img.type(), cv::Scalar(0));
    
    cv::Point center(balls[0].x + cvRound(balls[0].width * 0.5), cvRound(balls[0].y + balls[0].height * 0.5));
    cv::circle(mask, center, cvRound(balls[0].width * 0.5), cv::Scalar(255, 255, 255), -1);

    cv::bitwise_and(mask, img, maskedCircle);

    double tresh = cv::threshold(maskedCircle, dest, 1, 255, CV_THRESH_BINARY);

    std::vector<std::vector<cv::Point> > contours;
    cv::Mat contourOutput = dest.clone();
    cv::findContours(dest, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    if (!contours.size())
    {
        LOG_DBG("BallFilter::CropBall -- contours not found");
        return false;
    }

    auto maxVector = std::max_element(contours.begin(), contours.end(),
        [](std::vector<cv::Point>& lhs, std::vector<cv::Point>& rhs)
    {
        return lhs.size() < rhs.size();
    });

    m_cropedROI = cv::boundingRect(*maxVector);
    m_croppedBallMat = m_originMat(m_cropedROI);

    return true;
}

bool BallFilter::DetectBall()
{
    LOG_DBG("BallFilter::DetectBall");
    cv::Mat grayMat, workMat;
    workMat = m_originMat.clone();
    cv::cvtColor(workMat, grayMat, CV_BGR2GRAY);
    cv::equalizeHist(grayMat, grayMat);

    std::vector<cv::Rect> balls;
    m_ball_cascade.detectMultiScale(grayMat, balls, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(50, 50));

    if (!balls.size())
    {
        return false;
    }

    if (!CropBall(grayMat, balls))
        return false;

    for (size_t i = 0; i < balls.size(); i++)
    {
        cv::Point center(balls[i].x + cvRound(balls[i].width * 0.5), cvRound(balls[i].y + balls[i].height * 0.5));
        circle(m_originMat, center, cvRound(balls[i].width * 0.5), cv::Scalar(255, 0, 255), 4, 8, 0);
    }

    return true;

}

