#pragma once
#include <SDL.h>
#include <glm\glm.hpp>
#include <vector>



class Input
{
public:
	enum MouseButtons
	{
		Left,
		Middle,
		Right
	};

	static void Update();

	static glm::vec2 GetArrowDir();

	/// Handling Mouse Event
	static void onMouseButtonDown(SDL_Event& event);
	static void onMouseMove(SDL_Event& event);
	static void onMouseButtonUp(SDL_Event& event);
	static bool getMouseButtonState(int buttonNumber);
	static glm::vec2* getMousePosition();

	///Handling Keyboard Event
	static void onKeyDown();
	static void onKeyUp();
	static bool isKeyDown(SDL_Scancode key);
	static bool Quit();

private:

	static std::vector<bool> m_mouseButtonStates;
	static glm::vec2 m_mousePosition;
	static Uint8* m_keystates;
	static bool m_quit;
};

