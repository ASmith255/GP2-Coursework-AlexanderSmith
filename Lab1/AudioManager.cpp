#include "AudioManager.h"

AudioManager::AudioManager()
{
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

	//Checking for errors in the audio player. Prints an error message to the screen and quits if one is found.
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
		exit(-1);
	}
}


AudioManager::~AudioManager()
{
	SDL_Quit();
}


void AudioManager::addAudioClip(const char* filePath)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(filePath);		//Saves a pointer to the audio file that the program is trying to load.

	if (tmpChunk != nullptr)		//If the audio file could be loaded,
	{
		audioClips.push_back(tmpChunk);		//Add it to the list of audio clips and print a message to the console.
		std::cout << (audioClips.size() - 1) << " Sound is Ready, path: " << filePath << '\n';
	}
	else
	{
		//Otherwise, print an error message to the console.
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
	}
}


void AudioManager::addAudioTrack(const char* filePath)
{
	ambientMusic = Mix_LoadMUS(filePath);		//Loads the audio file at the given file path.

	if (ambientMusic == NULL)		//If it fails to load, print an error message.
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}


void AudioManager::playAudioClip(const int index)
{
	if (index > audioClips.size() - 1)		//If the given index is not valid,
	{
		std::cout << "Sound out of range.\n";		//Print a message about this issue to the console.
		return;
	}
	
	//Else, play the audio clip.
	Mix_PlayChannel(-1, audioClips[index], 0);
	std::cout << "Played Sound: " << index << '\n';
}


void AudioManager::playAudioTrack()
{
	if (Mix_PlayingMusic() == 0)		//If an audio track isn't already playing,
	{
		Mix_PlayMusic(ambientMusic, -1);		//Play the track.
	}
}