#pragma once

#include "audio_stream.h"

//#define READ_CHAR_ARRAY2(Buffer, InArray, Index) \
//Buffer[0] = InArray[Index]; \
//Buffer[1] = InArray[Index+1]; \
//Index += 2; \
//
//#define READ_CHAR_ARRAY4(Buffer, InArray, Index) \
//Buffer[0] = InArray[Index]; \
//Buffer[1] = InArray[Index+1]; \
//Buffer[2] = InArray[Index+2]; \
//Buffer[3] = InArray[Index+3]; \
//Index += 4; \

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
