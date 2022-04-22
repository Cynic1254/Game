#pragma once
#include <SDL.h>

class AudioPlayer
{
public:
  AudioPlayer(const char* audio);

  void PlaySound();

  ~AudioPlayer();

private:
  SDL_AudioSpec audioSpec_;
  Uint32 audioLength_;
  Uint8* audioBuffer_;

  SDL_AudioDeviceID deviceId_;
};
