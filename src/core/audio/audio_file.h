#pragma once

class AudioFile {
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

    void Initialize();
    void Destroy();
    void Play();
    bool IsPlaying();
    void UpdateStream();
};
