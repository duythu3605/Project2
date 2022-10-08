#include "AudioManager.h"
#include "Constant.h"
#include "GameManager.h"
#include "AudioEngine.h"


USING_NS_CC;
using namespace experimental;
int AudioManager::id_sword_sound = -1;


void AudioManager::init() {

}
void AudioManager::set_idSoundSword(string n , bool isloop) {
	AudioManager::id_sword_sound = AudioEngine::play2d(n, isloop);
	//AudioData::iid_Sword_sound = new int (AudioEngine::play2d(n, isloop));
	//CCLOG("%d , alo", AudioData::iid_Sword_sound);
}

int AudioManager::get_idSoundSword() {
	return AudioManager::id_sword_sound;
}
