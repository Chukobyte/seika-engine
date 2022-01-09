#pragma once

#include "audio_stream.h"

class AudioStreamHelper {
  private:
    static std::int32_t ConvertToInt(char* buffer, std::size_t len);
    static void ReadBuffer(char* outBuffer, unsigned char* inBuffer, unsigned int readLength, unsigned int& readIndex);
    static bool LoadWavFileHeader(std::ifstream& file, AudioStream* audioFileData);
    static bool LoadWavFileHeaderFromMemory(unsigned char* fileBuffer, size_t fileBufferSize, AudioStream* audioFileData);

  public:
    static AudioStream* LoadWav(const std::string& filename, float pitch = 1.0f, float gain = 1.0f, bool loops = false);
    static AudioStream* LoadWavFromMemory(void* fileBuffer, size_t fileBufferSize, float pitch = 1.0f, float gain = 1.0f, bool loops = false);
};
