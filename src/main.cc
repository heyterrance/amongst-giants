// main.cc
// Terrance Howard (heyterrance@gmail.com)

#include <stdio.h> // printf
#include <locale.h> // setlocale, LC_NUMERIC
#include <sstream> // std::stringstream
#include <thread> // std::thread

#include <SFML/System.hpp> // sf::Clock, sf::Time
#include <SFML/Window.hpp> // sf::Event
#include <SFML/Graphics.hpp> // sf::RenderWindow, sf::Color

#include "util.h" // dbprintf
#include "constants.h" // WIN_WIDTH, WIN_HEIGHT
#include "state.h" // StateManager
#include "intro_state.h" // IntroState
#include "world_state.h" // WorldState

typedef struct _window_status {
  bool isOpen;
  bool focused;
  _window_status(bool open, bool focused) : isOpen(open), focused(focused) { }
} WindowStatus;

void runLogic(const WindowStatus& stat, StateManager& manager);
void runGraphics(WindowStatus& stat, const StateManager& manager);

int main(int, char** argv) {
  setlocale(LC_NUMERIC, "");
  printf("======================================");
  printf("======================================\n");
  printf("                              Amongst Giants\n");
  dbprintf("                               (DEBUG MODE)\n");
  printf("======================================");
  printf("======================================\n\n");

  // Get path to executable 
  std::string exec_path(argv[0]);
  exec_path = exec_path.substr(0, exec_path.find_last_of('/') + 1);
  
  // Use absolute path for resources
  FontManager::setPath(exec_path);
  TextureManager::setPath(exec_path);
  RoomManager::setPath(exec_path);

  // Variables shared between threads
  WindowStatus stat(false, true);
  StateManager manager;

#ifndef DEBUG
  manager.push(new IntroState());
#else
  manager.push(new WorldState());
#endif

  std::thread logicThread(runLogic, std::ref(stat), std::ref(manager));
  runGraphics(stat, manager);
  logicThread.join();

  return 0;
}


void runGraphics(WindowStatus& stat, const StateManager& manager) {
  // Setup window
  const sf::VideoMode mode(WIN_WIDTH, WIN_HEIGHT, 8);
  sf::RenderWindow window(mode, "Amongst Giants", sf::Style::Close);
  window.setVerticalSyncEnabled(true);

#ifdef DEBUG
  sf::Clock clock;
  int_fast16_t count = 0;
  float elapsed = 0.0f;
#endif

  while ( (stat.isOpen = window.isOpen()) ) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed: window.close(); break;
        case sf::Event::LostFocus: stat.focused = false; break;
        case sf::Event::GainedFocus: stat.focused = true; break;
        default: break;
      }
    }

    if (not stat.focused) {
#ifdef DEBUG
      clock.restart();
#endif
      continue;
    }

    window.clear(sf::Color(250, 255, 250));
    manager.draw(window);
    window.display();

#ifdef DEBUG
    elapsed += clock.restart().asSeconds();
    if (++count >= 650) {
      printf("[Graphic] %'.4G FPS (%'d frames)\n",
          static_cast<float>(count)/elapsed, count);
      count = 0;
      elapsed = 0.0f;
    }
#endif
  }
}

void runLogic(const WindowStatus& stat, StateManager& manager) {
  sf::Clock clock;

  // Wait for window to open
  // Reason for "clock.restart()": Optimized compilation skips over empty
  //                               while loop
  // TODO: Look for more intelligent workaround
  while (not stat.isOpen)
    clock.restart();

#ifdef DEBUG
  uint_fast64_t count = 0;
  float elapsed = 0.0f;
#endif

  while (stat.isOpen) {
    const float dt = clock.restart().asSeconds();

    if (not stat.focused)
      continue;

    manager.update(dt);

#ifdef DEBUG
    elapsed += dt;
    if (++count >= 2E6) {
      printf("[Logic]   %'.4G SPS (%'llu steps)\n",
             static_cast<float>(count)/elapsed, count);
      count = 0llu;
      elapsed = 0.0f;
    }
#endif
  }
}
