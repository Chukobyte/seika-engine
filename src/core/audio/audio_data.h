#pragma once

#include <iostream>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>

enum class Endian {
#ifdef _WIN32
    little = 0,
    big    = 1,
    native = little
#else
    little = __ORDER_LITTLE_ENDIAN__,
    big    = __ORDER_BIG_ENDIAN__,
    native = __BYTE_ORDER__
#endif
};

static void ALErrorHelper(const std::string& context) {
    ALCenum error = alGetError();
    if (error != AL_NO_ERROR) {
        std::cerr << "[" << context << "] " << "error code: " << error << std::endl;
        switch (error) {
        case AL_INVALID_NAME:
            std::cerr << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function" << std::endl;
            break;
        case AL_INVALID_ENUM:
            std::cerr << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function" << std::endl;
            break;
        case AL_INVALID_VALUE:
            std::cerr << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function" << std::endl;
            break;
        case AL_INVALID_OPERATION:
            std::cerr << "AL_INVALID_OPERATION: the requested operation is not valid" << std::endl;
            break;
        case AL_OUT_OF_MEMORY:
            std::cerr << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory"
                      << std::endl;
            break;
        default:
            std::cerr << "Unknown AL Error!" << std::endl;
            break;
        }
    } else {
        std::cerr << "No error for '" << context << "'!" << std::endl;
    }
}

