#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

namespace zbe {
	class AudioSystem {
	public:
		void Start();
		void Shutdown();
		void Update(float dt);
		void AddAudio(const std::string& name, const std::string& filename);
		void PlayAudio(const std::string& name);
	private:
		FMOD::System* sys;
		std::map<std::string, FMOD::Sound*> sounds;
	};
}

extern zbe::AudioSystem g_audio;

