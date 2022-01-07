#pragma once

#include <vector>

#include "audio_data.h"

class AudioStream {
  public:
    ALenum format;
    ALuint source;
    ALsizei fileSize;
    ALsizei dataSize;
    std::uint8_t channels;
    std::int32_t sampleRate;
    std::uint8_t bitsPerSample;
    std::vector<char> data;
    ALint state = AL_NONE;
    ALuint buffer;

    AudioStream() = default;
    AudioStream(float initialPitch, float initialGain, bool loops);
    void Initialize();
    void Destroy();
    void Play();
    void Stop();
    bool IsPlaying();
    float GetPitch();
    void SetPitch(float newPitch);
    float GetGain();
    void SetGain(float newGain);
    bool DoesLoop();
    void SetLoops(bool value);

  private:
    static const std::size_t NUM_BUFFERS = 4;
    static const std::size_t BUFFER_SIZE = 65536; // 32kb of data in each buffer

    ALuint buffers[NUM_BUFFERS];
    std::size_t cursor;

    float pitch = 1.0f;
    float gain = 1.0f;
    bool loops = false;
};
