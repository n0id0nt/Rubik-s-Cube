#include "Input.h"

std::vector<bool> Input::m_mouseButtonStates { false, false, false };
glm::vec2 Input::m_mousePosition(0,0);
Uint8* Input::m_keystates(0);
bool Input::m_quit(false);

void Input::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
        case SDL_KEYDOWN:
            onKeyDown();
            break;
        case SDL_KEYUP:
            onKeyUp();
            break;
        default:
            break;

        }
    }
}

glm::vec2 Input::GetArrowDir()
{
    int x = isKeyDown(SDL_SCANCODE_RIGHT) - isKeyDown(SDL_SCANCODE_LEFT);
    int y = isKeyDown(SDL_SCANCODE_UP) - isKeyDown(SDL_SCANCODE_DOWN);
    return glm::vec2(x, y);
}

glm::vec2* Input::getMousePosition()
{
    return &m_mousePosition;
}

bool Input::isKeyDown(SDL_Scancode key)
{
    if (m_keystates != 0)
    {
        if (m_keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

void Input::onKeyDown()
{
    m_keystates = (Uint8*)SDL_GetKeyboardState(0);
}

void Input::onKeyUp()
{
    m_keystates = (Uint8*)SDL_GetKeyboardState(0);
}

bool Input::Quit()
{
    return m_quit;
}

void Input::onMouseButtonDown(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[Left] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[Middle] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[Right] = true;
    }
}

void Input::onMouseMove(SDL_Event& event)
{
    m_mousePosition.x = event.motion.x;
    m_mousePosition.y = event.motion.y;
}

void Input::onMouseButtonUp(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[Left] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[Middle] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[Right] = false;
    }
}

bool Input::getMouseButtonState(int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}