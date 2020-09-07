#include <opencv2/highgui.hpp>
//====================================
#include <iostream>
#include <thread>
#include <chrono>
//====================================
#include "FiltersHandler.h"
#include "Logger.h"


int main(int argc, char* argv[])
{
    cv::CommandLineParser parser(argc, argv, "{@image_path||}");
    std::string image_path = parser.get<std::string>(0);

    std::shared_ptr<FileLogger> logger;
    logger.reset(FileLogger::get_logger("FiltersHandler"));
    std::unique_ptr <FiltersHandler> handler = std::make_unique<FiltersHandler>();
    if (handler)
    {
        handler->Init(image_path);
        handler->Start();
        while (!handler->Stopped())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if(handler->Stopped())
                break;
        }
    }


 
    return 0;
}
