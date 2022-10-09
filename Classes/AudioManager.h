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
	
	static int id_pain_sound;
	static int id_sworddown_sound;
	static int id_swordcut_sound;
	static int id_Bomb_down_sound;
	static int id_Bomb_explo_sound;
	static int id_Rock_down_sound;
	static int id_Rock_explo_sound;
	static int id_SL_down_sound;
	static int id_SL_explo_sound;

	static int id_BG1;
	static int id_BG2;

	static void init();
	static void set_idSoundSword(string n , bool k);
	static int get_idSoundSword();

	static void set_idSoundSword_cut(string n, bool k);
	static int get_idSoundSword_cut();

	static void set_idBombDown(string n, bool k);
	static int get_idBombDown();

	static void set_idBombExplo(string n, bool k);
	static int get_idBombExplo();

	static void set_idRockDown(string n, bool k);
	static int get_idRockDown();

	static void set_idRockExplo(string n, bool k);
	static int get_idRockExplo();

	static void set_idSLDown(string n, bool k);
	static int get_idSLDown();

	static void set_idSLExplo(string n, bool k);
	static int get_idSLExplo();

	static void set_idPain(string n, bool k);
	static int get_idPain();

	static void set_idBG(string n, bool k);
	static int get_idBG();

	static void set_idBG2(string n, bool k);
	static int get_idBG2();

	static void StopMusic(int idsound);
	static void PauseSound();
	static void ResumeSound();
 	
};

#endif // __AUDIO_MANAGER_H__
