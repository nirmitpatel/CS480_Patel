
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;
  int keystroke = 0;
  int mouseclick = 0;
  bool toggle = true;
  bool unpause = true;
  bool orbit = true;
  bool spin = true;
  bool moon = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard(keystroke, toggle, unpause, orbit, spin, moon);
      Mouse(mouseclick, toggle, unpause, orbit);
    }

    // Update and render the graphics
    m_graphics->Update(m_DT, keystroke, mouseclick);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard(int &keystroke, bool &toggle, bool &unpause, bool &orbit, bool &spin, bool &moon)
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here

    // if ESCAPE pressed --> quit
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
    // if SPACE pressed once --> pause
    else if (m_event.key.keysym.sym == SDLK_SPACE && unpause == true)
    {
      keystroke = 1;
      unpause = false;
    }
    // if SPACE pressed again --> unpause (normal)
    else if (m_event.key.keysym.sym == SDLK_SPACE && unpause == false)
    {
      keystroke = 0;
      unpause = true;
    }
    // if right ALT pressed once --> reverse
    else if (m_event.key.keysym.sym == SDLK_RALT && toggle == true && unpause == true)
    {
      keystroke = 2;
      toggle = false;
    }
    // if right ALT pressed again --> normal
    else if (m_event.key.keysym.sym == SDLK_RALT && toggle == false && unpause == true)
    {
      keystroke = 0;
      toggle = true;
    }
    // if right CTRL pressed once --> stop spinning
    else if (m_event.key.keysym.sym == SDLK_RCTRL && spin == true && unpause == true)
    {
      keystroke = 3;
      spin = false;
    }
    // if right CTRL pressed again --> normal
    else if (m_event.key.keysym.sym == SDLK_RCTRL && spin == false && unpause == true)
    {
      keystroke = 0;
      spin = true;
    }
    // if DELETE pressed once --> stop orbit
    else if (m_event.key.keysym.sym == SDLK_DELETE && orbit == true && unpause == true)
    {
      keystroke = 4;
      orbit = false;
    }
    // if DELETE pressed again --> normal
    else if (m_event.key.keysym.sym == SDLK_DELETE && orbit == false && unpause == true)
    {
      keystroke = 0;
      orbit = true;
    }
    // if TAB pressed once --> reverse moon
    else if (m_event.key.keysym.sym == SDLK_TAB && moon == true && unpause == true)
    {
      keystroke = 5;
      moon = false;
    }
    // if TAB pressed again --> normal
    else if (m_event.key.keysym.sym == SDLK_TAB && moon == false && unpause == true)
    {
      keystroke = 0;
      moon = true;
    }
  }
}

void Engine::Mouse(int &mouseclick, bool &toggle, bool &unpause, bool &orbit)
{
  if (m_event.type == SDL_MOUSEBUTTONDOWN)
  {
    // handle mouse click events here

    // if left mouse clicked once --> reverse
    if (m_event.button.button == SDL_BUTTON_LEFT && toggle == true && unpause == true)
    {
      mouseclick = 2;
      toggle = false;
    }
    // if left mouse clicked again --> normal
    else if (m_event.button.button == SDL_BUTTON_LEFT && toggle == false && unpause == true)
    {
      mouseclick = 0;
      toggle = true;
    }
    // if right mouse clicked once --> stop spinning
    else if (m_event.button.button == SDL_BUTTON_RIGHT && orbit == true && unpause == true)
    {
      mouseclick = 3;
      orbit = false;
    }
    // if right mouse clicked again --> normal
    else if (m_event.button.button == SDL_BUTTON_RIGHT && orbit == false && unpause == true)
    {
      mouseclick = 0;
      orbit = true;
    }
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
















