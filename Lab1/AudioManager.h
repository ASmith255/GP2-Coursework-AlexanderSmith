#pragma once
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <iostream>
#include <vector>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void addAudioClip(const char* filePath);
	void addAudioTrack(const char* filePath);
	void playAudioClip(const int index);
	void playAudioTrack();

private:
	Mix_Music* ambientMusic;		//Audio track that plays in the background of the game
	std::vector<Mix_Chunk*> audioClips;		//Vector containing all audio clips
};