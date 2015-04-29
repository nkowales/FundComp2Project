/*
*
*	JukeBox.cpp
*	Created on 28 April, 2015
*	by: mtroy
*
*/
#include "JukeBox.h"

JukeBox::JukeBox(Uint32 id) : WorldObject(id)
{

}
void JukeBox::init(ContentManager* content)
{
	song = content->getMusic(songName);

	if (song)
		playMusic();
}

void JukeBox::uninit()
{
	//Mix_HaltMusic();
}

void JukeBox::playMusic()
{
	//SDL_ClearError();
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(song,-1);
	}
	//cout << SDL_GetError() << endl;
}
void JukeBox::setProperty(string name, string location)
{
	if (name == "song")
		songName = location;
	else
		WorldObject::setProperty(name, location);
}
