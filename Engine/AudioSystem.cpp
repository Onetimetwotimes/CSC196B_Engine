#include "AudioSystem.h"

zbe::AudioSystem g_audio;

void zbe::AudioSystem::Start() {
	FMOD::System_Create(&sys); 
	void* extradriverdata = nullptr;
	sys->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void zbe::AudioSystem::Shutdown() {
	for (auto& sound : sounds) {
		sound.second->release();
	}
	sounds.clear(); 
	sys->close(); sys->release();
}

void zbe::AudioSystem::Update(float dt) {
	sys->update();
}

void zbe::AudioSystem::AddAudio(const std::string& name, const std::string& filename) {
	if (sounds.find(name) == sounds.end()) {
		FMOD::Sound* sound{ nullptr };
		sys->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		sounds[name] = sound; 
	}
}

void zbe::AudioSystem::PlayAudio(const std::string& name) {
	auto iter = sounds.find(name); 
	if (iter != sounds.end()) {
		FMOD::Sound* sound = iter->second; 
		sound->setMode(FMOD_LOOP_OFF);
		FMOD::Channel* channel; 
		sys->playSound(sound, 0, false, &channel); 
	}
}
