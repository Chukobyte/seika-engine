#include "audio_file_data.h"

#include <cstring>

void AudioFileData::Initialize() {
    if (channels == 1 && bitsPerSample == 8) {
        format = AL_FORMAT_MONO8;
    } else if (channels == 1 && bitsPerSample == 16) {
        format = AL_FORMAT_MONO16;
    } else if (channels == 2 && bitsPerSample == 8) {
        format = AL_FORMAT_STEREO8;
    } else if (channels == 2 && bitsPerSample == 16) {
        format = AL_FORMAT_STEREO16;
    } else {
        std::cerr << "Wave format not recognised!" << std::endl;
    }

    // Buffer
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, data.data(), data.size(), sampleRate);

    // Source
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(source, AL_LOOPING, loops ? AL_TRUE : AL_FALSE);
    alSourcei(source, AL_BUFFER, buffer);
}

void AudioFileData::Destroy() {
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}

void AudioFileData::Play() {
    alSourcePlay(source);
}

bool AudioFileData::IsPlaying() {
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

void AudioFileData::UpdateStream() {
    ALint buffersProcessed = 0;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffersProcessed);

    if (buffersProcessed <= 0) {
        std::cout << "No buffers processed..." << std::endl;
        return;
    }
    std::cout << "Buffers processed = " << buffersProcessed << std::endl;

    while (buffersProcessed--) {
        ALuint buff;
        alSourceUnqueueBuffers(source, 1, &buff);
        ALErrorHelper(std::string("alSourceUnqueueBuffers - buff: " + std::to_string(buff)));

        ALsizei bufferDataSize = BUFFER_SIZE;

        char *buffData = new char[bufferDataSize];
        std::memset(buffData, 0, bufferDataSize);

        std::size_t dataSizeToCopy = BUFFER_SIZE;
        if (cursor + BUFFER_SIZE > data.size()) {
            dataSizeToCopy = data.size() - cursor;
        }

        std::memcpy(&data[0], &data[cursor], dataSizeToCopy);
        cursor += dataSizeToCopy;

        if (dataSizeToCopy < BUFFER_SIZE) {
            cursor = 0;
            std::memcpy(&data[dataSizeToCopy], &data[cursor], BUFFER_SIZE - dataSizeToCopy);
            cursor = BUFFER_SIZE - dataSizeToCopy;
        }

        alBufferData(buff, format, buffData, BUFFER_SIZE, sampleRate);
        alSourceQueueBuffers(source, 1, &buff);
        ALErrorHelper(std::string("alSourceQueueBuffers - buff: " + std::to_string(buff)));

        delete buffData;
    }
}
