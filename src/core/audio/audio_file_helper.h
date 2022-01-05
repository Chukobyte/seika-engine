#pragma once

#include "audio_file_data.h"

class AudioFileHelper {
  private:
    static std::int32_t ConvertToInt(char* buffer, std::size_t len) {
        std::int32_t a = 0;
        if(Endian::native == Endian::little) {
            std::memcpy(&a, buffer, len);
        } else {
            for (std::size_t i = 0; i < len; ++i) {
                reinterpret_cast<char *>(&a)[3 - i] = buffer[i];
            }
        }
        return a;
    }

    static bool LoadWavFileHeader(std::ifstream& file, AudioFileData* audioFileData) {
        char buffer[4];
        if(!file.is_open()) {
            return false;
        }

        // the RIFF
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read RIFF" << std::endl;
            return false;
        }
        if(std::strncmp(buffer, "RIFF", 4) != 0) {
            std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
            return false;
        }

        // the size of the file
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read size of file" << std::endl;
            return false;
        }
        audioFileData->fileSize = ConvertToInt(buffer, 4);

        // the WAVE
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read WAVE" << std::endl;
            return false;
        }
        if(std::strncmp(buffer, "WAVE", 4) != 0) {
            std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
            return false;
        }

        // "fmt/0"
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read fmt/0" << std::endl;
            return false;
        }

        // this is always 16, the size of the fmt data chunk
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read the 16" << std::endl;
            return false;
        }

        // PCM should be 1?
        if(!file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read PCM" << std::endl;
            return false;
        }

        // the number of channels
        if(!file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read number of channels" << std::endl;
            return false;
        }
        audioFileData->channels = ConvertToInt(buffer, 2);

        // sample rate
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read sample rate" << std::endl;
            return false;
        }
        audioFileData->sampleRate = ConvertToInt(buffer, 4);

        // byte rate
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read byte rate" << std::endl;
            return false;
        }

        // block align
        if(!file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read block align" << std::endl;
            return false;
        }

        // bitsPerSample
        if(!file.read(buffer, 2)) {
            std::cerr << "ERROR: could not read bits per sample" << std::endl;
            return false;
        }
        audioFileData->bitsPerSample = ConvertToInt(buffer, 2);

        // sub chunk id
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read data chunk header" << std::endl;
            return false;
        }
        // sub chunk size
        if(std::strncmp(buffer, "data", 4) != 0) {
            std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
            return false;
        }

        // size of data
        if(!file.read(buffer, 4)) {
            std::cerr << "ERROR: could not read data size" << std::endl;
            return false;
        }
        audioFileData->dataSize = ConvertToInt(buffer, 4);

        /* cannot be at the end of file */
        if(file.eof()) {
            std::cerr << "ERROR: reached EOF on the file" << std::endl;
            return false;
        }
        if(file.fail()) {
            std::cerr << "ERROR: fail state set on the file" << std::endl;
            return false;
        }

        return true;
    }
  public:
    static AudioFileData* LoadWav(const std::string& filename) {
        AudioFileData *audioFileData = new AudioFileData();
        std::ifstream fileStream(filename, std::ios::binary);
        if(!fileStream.is_open()) {
            std::cerr << "ERROR: Could not open \"" << filename << "\"" << std::endl;
            return audioFileData;
        }

        if(!LoadWavFileHeader(fileStream, audioFileData)) {
            std::cerr << "ERROR: Could not load wav header of \"" << filename << "\"" << std::endl;
            return audioFileData;
        }

        fileStream.clear();
        fileStream.seekg(0, std::ios::beg);
        audioFileData->data = {std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>()};
        audioFileData->data.resize(audioFileData->dataSize);
        audioFileData->Initialize();

        return audioFileData;
    }
};