#pragma once

#include <vector>

#include "audio_data.h"

class AudioFileData {
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
    bool loops = false;

    void Initialize();
    void Destroy();
    void Play();
    bool IsPlaying();
    void UpdateStream();

  private:
    static const std::size_t NUM_BUFFERS = 4;
    static const std::size_t BUFFER_SIZE = 65536; // 32kb of data in each buffer

    ALuint buffers[NUM_BUFFERS];
    std::size_t cursor;
};
