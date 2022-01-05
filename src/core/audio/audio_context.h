#pragma once

#include "../utils/singleton.h"

#include <AL/al.h>
#include <AL/alc.h>

class AudioContext : public Singleton<AudioContext> {
  private:
    ALCdevice *device = nullptr;
    ALCcontext *context = nullptr;

    ALuint buffer;
    ALenum format;

  public:
    AudioContext(singleton) {}

    bool Initialize() {
        device = alcOpenDevice(nullptr);
        if (!device) {
            return false;
        }

        context = alcCreateContext(device, nullptr);
        if (!context) {
            return false;
        }

        ALCboolean contextMadeCurrent = alcMakeContextCurrent(context);
        if (!contextMadeCurrent) {
            return false;
        }

        alGenBuffers(1, &buffer);

        return true;
    }

    bool ShutDown() {
        alDeleteBuffers(1, &buffer);
        alcMakeContextCurrent(context);
        alcDestroyContext(context);
        return (bool) alcCloseDevice(device);
    }
};
