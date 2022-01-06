#pragma once

#include "audio_file_data.h"

class AudioFileHelper {
  private:
    static std::int32_t ConvertToInt(char* buffer, std::size_t len);
    static bool LoadWavFileHeader(std::ifstream& file, AudioFileData* audioFileData);

  public:
    static AudioFileData* LoadWav(const std::string& filename, bool loops);
};