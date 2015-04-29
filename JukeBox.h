#ifndef JUKEBOX_H_
#define JUKEBOX_H_
#include <map>
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "AnimatedTexture.h"
#include <SDL2/SDL_mixer.h>
#include "WorldObject.h"

using namespace std;

class JukeBox : public WorldObject
{
public:
	JukeBox(Uint32);
	void init(ContentManager* content);
	void uninit();
	virtual void setProperty(string, string);
	void playMusic();
private:
	string songName = "";
	Mix_Music* song = NULL;
	
};


#endif
