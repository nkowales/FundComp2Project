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
}
void JukeBox::playMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(song,-1);
	}
}
void JukeBox::setProperty(string name, string location)
{
	songName = name;
	songLocation = location;

}
