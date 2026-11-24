// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Core/File.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Pipeline.h"
#include "Components/CameraComponent.h"
#include "Resources/ResourceManager.h"
#include "Framework/Scene.h"

#include <fmod.hpp>

#include <iostream>
#include <vector>
#include "SDL3/SDL.h"
#include <map>
#include <memory>
#include <random>
#include <fstream>

#define GLM_ENABLE_EXPERIMENTAL

#define MAX(a, b) ((a > b) ? a : b)

using namespace nu;

int main() {
	SetWorkingDirectory("assets"); //Keep this at the top of main() to ensure the working directory is set before any assets are loaded

	//INITIALIZATION
    Engine::Get().Initialize();

	Scene scene;
	scene.Load("scenes/scene_skybox.json");
    
	auto& renderer = Engine::Get().GetRenderer();

    //MAIN LOOP
    bool quit = false;
    while (!quit) {

        //UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            Engine::Get().GetEditor().ProcessEvent(event);

            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
            }
        }

        //ENGINE
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();
		float time = Engine::Get().GetTime().GetTime();

        //SCENE
        scene.Update(dt);

        //EDITOR
        Engine::Get().GetEditor().BeginFrame();
        Engine::Get().GetEditor().Update(scene);


        // RENDER
        renderer.BeginFrame();

		scene.Draw(renderer);

        Engine::Get().GetRenderer().EndRenderPass();
        Engine::Get().GetEditor().Draw(renderer);

        renderer.EndFrame();
    }

    //SHUTDOWN
    Engine::Get().Shutdown();


    return 0;
}