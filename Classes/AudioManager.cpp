#include "AudioManager.h"
#include "Constant.h"
#include "GameManager.h"
#include "AudioEngine.h"


USING_NS_CC;
using namespace experimental;
int AudioManager::id_pain_sound = -1;
int AudioManager::id_sworddown_sound = -1;
int AudioManager::id_swordcut_sound = -1;

int AudioManager::id_Bomb_down_sound = -1;
int AudioManager::id_Bomb_explo_sound = -1;

int AudioManager::id_Rock_down_sound = -1;
int AudioManager::id_Rock_explo_sound = -1;

int AudioManager::id_SL_down_sound = -1;
int AudioManager::id_SL_explo_sound = -1;

int AudioManager::id_BG1 = -1;
int AudioManager::id_BG2 = -1;

void AudioManager::init() {

}
void AudioManager::set_idPain(string n, bool isloop) {
	AudioManager::id_pain_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idPain() {
	return AudioManager::id_pain_sound;
}
void AudioManager::set_idSoundSword(string n , bool isloop) {
	AudioManager::id_sworddown_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idSoundSword() {
	return AudioManager::id_sworddown_sound;
}
void AudioManager::set_idSoundSword_cut(string n, bool isloop) {
	AudioManager::id_swordcut_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idSoundSword_cut() {
	return AudioManager::id_swordcut_sound;
}

void AudioManager::set_idBombDown(string n, bool isloop) {
	AudioManager::id_Bomb_down_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idBombDown() {
	return AudioManager::id_Bomb_down_sound;
}

void AudioManager::set_idBombExplo(string n, bool isloop) {
	AudioManager::id_Bomb_explo_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idBombExplo() {
	return AudioManager::id_Rock_explo_sound;
}

void AudioManager::set_idRockDown(string n, bool isloop) {
	AudioManager::id_Rock_down_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idRockDown() {
	return AudioManager::id_Rock_down_sound;
}

void AudioManager::set_idRockExplo(string n, bool isloop) {
	AudioManager::id_Rock_explo_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idRockExplo() {
	return AudioManager::id_Rock_explo_sound;
}

void AudioManager::set_idSLDown(string n, bool isloop) {
	AudioManager::id_SL_down_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idSLDown() {
	return AudioManager::id_SL_down_sound;
}

void AudioManager::set_idSLExplo(string n, bool isloop) {
	AudioManager::id_SL_explo_sound = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idSLExplo() {
	return AudioManager::id_SL_explo_sound;
}

void AudioManager::set_idBG(string n, bool isloop) {
	AudioManager::id_BG1 = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idBG() {
	return AudioManager::id_BG1;
}

void AudioManager::set_idBG2(string n, bool isloop) {
	AudioManager::id_BG2 = AudioEngine::play2d(n, isloop);

}

int AudioManager::get_idBG2() {
	return AudioManager::id_BG2;
}

void AudioManager::StopMusic(int idsound) {
	AudioEngine::stop(idsound);
}

void AudioManager::PauseSound() {
	AudioEngine::pauseAll();
}
void AudioManager::ResumeSound() {
	AudioEngine::resumeAll();
}

