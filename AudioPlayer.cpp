#include "AudioPlayer.h"

#include <iostream>

AudioPlayer::AudioPlayer(const char* audio)
{
  if (SDL_LoadWAV(audio, &audioSpec_, &audioBuffer_, &audioLength_) == NULL)
  {
    std::cout << "Could not open " << audio << ": " << SDL_GetError() << std::endl;
  }

  deviceId_ = SDL_OpenAudioDevice(NULL, 0, &audioSpec_, NULL, 0);
}

void AudioPlayer::PlaySound() const
{
  SDL_QueueAudio(deviceId_, audioBuffer_, audioLength_);
  SDL_PauseAudioDevice(deviceId_, 0);
}

AudioPlayer::~AudioPlayer()
{
  SDL_CloseAudioDevice(deviceId_);
  SDL_FreeWAV(audioBuffer_);
}
