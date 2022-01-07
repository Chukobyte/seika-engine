#include "audio_stream.h"

#include <cstring>

AudioStream::AudioStream(float initialPitch, float initialGain, bool loops) : pitch(initialPitch), gain(initialGain), loops(loops) {}

void AudioStream::Initialize() {
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
    SetPitch(pitch);
    SetGain(gain);
    alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(source, AL_LOOPING, loops ? AL_TRUE : AL_FALSE);
    alSourcei(source, AL_BUFFER, buffer);
}

void AudioStream::Destroy() {
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}

void AudioStream::Play() {
    alSourcePlay(source);
}

void AudioStream::Stop() {
    alSourceStop(source);
}

bool AudioStream::IsPlaying() {
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

float AudioStream::GetPitch() {
    return pitch;
}

void AudioStream::SetPitch(float newPitch) {
    pitch = newPitch;
    alSourcef(source, AL_PITCH, pitch);
}

float AudioStream::GetGain() {
    return gain;
}

void AudioStream::SetGain(float newGain) {
    gain = newGain;
    alSourcef(source, AL_GAIN, gain);
}

bool AudioStream::DoesLoop() {
    return loops;
}

void AudioStream::SetLoops(bool value) {
    loops = value;
}
