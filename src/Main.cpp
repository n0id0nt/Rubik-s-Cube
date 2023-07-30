#include <iostream>
#include <SDL.h>
#include <SDL_timer.h>

#include <GL\glew.h>
#include <vector>
#include <SDL_opengl.h>

#include "glm\glm.hpp"

#include "Scene.h"
#include "Camera.h"
#include "opengl\openglHelper.h"


const GLuint WIDTH = 800, HEIGHT = 600;
const unsigned int FPS = 60;
const unsigned int FRAME_DELAY = 1000 / FPS;
int SCREEN_WIDTH, SCREEN_HEIGHT;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("Rubik's Cube", WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

    std::cout << glGetString(GL_VERSION) << std::endl;

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

    SDL_Event e;

	Uint32 frameStart;
	unsigned int frameTime;

	// Setup some OpenGL options
	GLCall(glEnable(GL_DEPTH_TEST));

	// enable alpha support
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(WIDTH, HEIGHT);

	bool running = true;

    // game loop
	while (running)
	{
		frameStart = SDL_GetTicks();

		// Clear the colorbuffer
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) running = false;
			//cube.Input(e);
		}

		// Update
		scene->Update();

		// Render
		scene->Render();

		SDL_GL_SwapWindow(window);

		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	// Exit
    

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}