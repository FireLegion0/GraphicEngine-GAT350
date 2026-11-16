// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "Engine.h"

namespace nu {
	//Engine engine;

	bool Engine::Initialize() {
		m_renderer.Initialize("Game Engine", 1280, 1024);
		m_particleSystem.Initialize();
		m_input.Initialize();
		m_audio.Initialize();

		m_editor = std::make_unique<Editor>();
		m_editor->Initialize(m_renderer);

		return true;
	}

	void Engine::Shutdown() {
		m_input.Shutdown();
		m_particleSystem.Shutdown();
		m_editor->Shutdown();
		m_renderer.Shutdown();
		m_audio.Shutdown();
	}

	void Engine::Update() {
		m_time.Tick();
		m_input.Update();
		m_particleSystem.Update(m_time.GetDeltaTime());
		m_audio.Update();
	}
}