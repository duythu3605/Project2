#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include"AudioEngine.h"

USING_NS_CC;
using namespace std;
#pragma once

//namespace AudioData {
//	int* iid_Sword_sound;
//}


static class AudioManager
{
public:
	
	static int id_sword_sound;

	static void init();
	static void set_idSoundSword(string n , bool k);

	static int get_idSoundSword();
	
};

#endif // __AUDIO_MANAGER_H__
