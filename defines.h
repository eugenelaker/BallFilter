#pragma once

#define BALL_CLASSIFIER_XML "ball_cascade.xml"

enum class state_codes {
    STATE_SUCCEDED = 1,
    STATE_FAILER,
    STATE_ERROR_LOADING_IMAGE,
    OBJECT_NOT_DETECTED,
    CLASSIFIER_LOAD_FAIL,
};

enum class filter_types
{
    ball,
    face,
    plate,
};

enum class LogLevel
{
    none = 0,
    fatal = 1,
    error = 2,
    warning = 3,
    info = 4,
    debug = 5,
    trace = 6
};
