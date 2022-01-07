#pragma once

#include "audio_stream.h"

class AudioStreamHelper {
  private:
    static std::int32_t ConvertToInt(char* buffer, std::size_t len);
    static bool LoadWavFileHeader(std::ifstream& file, AudioStream* audioFileData);

  public:
    static AudioStream* LoadWav(const std::string& filename, float pitch = 1.0f, float gain = 1.0f, bool loops = false);
};