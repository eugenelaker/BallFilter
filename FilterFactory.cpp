#include "IFilter.h"
#include "BallFilter.h"


//---------------------------------------------------------------------
//  factory for filters. Choose which filter engine to use
//					create_filter
//---------------------------------------------------------------------
IFilter::ptr create_filter(filter_types type)
{
    switch (type)
    {
    case filter_types::ball:
        return std::make_shared<BallFilter>();
    case filter_types::face:
        break;
    case filter_types::plate:
        break;
    default:
        return nullptr;
        break;
    }

    return nullptr;

}
