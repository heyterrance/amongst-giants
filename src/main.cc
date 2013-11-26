// main.cc
// Terrance Howard (heyterrance@gmail.com)

#include <stdio.h> // printf
#include <locale.h> // setlocale, LC_NUMERIC
#include <sstream> // std::stringstream
#include <thread> // std::thread

#include <SFML/System.hpp> // sf::Clock, sf::Time
#include <SFML/Window.hpp> // sf::Event
#include <SFML/Graphics.hpp> // sf::RenderWindow, sf::Color

#include "constants.h"
#include "state.h" // StateManager
#include "intro_state.h"
#include "world_state.h"

typedef struct _window_status {
  bool isOpen;
  bool focused;
  _window_status(bool open, bool focused) : isOpen(open), focused(focused) { }
} WindowStatus;

void runLogic(const WindowStatus* stat, StateManager* manager);
void runGraphics(WindowStatus* stat, const StateManager* manager);

int main(int, char** argv) {
  setlocale(LC_NUMERIC, "");
  printf("======================================");
  printf("======================================\n");
  printf("                              Amongst Giants\n");
  printf("======================================");
  printf("======================================\n\n");

  std::string exec_path(argv[0]);
  exec_path = exec_path.substr(0, exec_path.find_last_of('/') + 1);

  FontManager::setPath(exec_path);
  TextureManager::setPath(exec_path);
  RoomManager::setPath(exec_path);

  WindowStatus stat(false, true);
  StateManager manager;
  // Skip intro for testing
  manager.push(new IntroState());
  // manager.push(std::shared_ptr<GameState>(new WorldState()));

  std::thread logicThread(runLogic, &stat, &manager);
  runGraphics(&stat, &manager);
  logicThread.join();
  return 0;
}


void runGraphics(WindowStatus* stat, const StateManager* manager) {
  // Setup window.
  const sf::VideoMode mode(WIN_WIDTH, WIN_HEIGHT, 8);
  sf::RenderWindow window(mode, "Amongst Giants", sf::Style::Close);
  window.setVerticalSyncEnabled(true);

#ifdef DEBUG
  sf::Clock clock;
  int_fast16_t count = 0;
  float elapsed = 0.0f;
#endif

  while ( (stat->isOpen = window.isOpen()) ) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed: window.close(); break;
        case sf::Event::LostFocus: stat->focused = false; break;
        case sf::Event::GainedFocus: stat->focused = true; break;
        default: break;
      }
    }

    if (!stat->focused) {
      // clock.restart();
      continue;
    }

#ifdef DEBUG
    elapsed += clock.restart().asSeconds();
    if (++count >= 650) {
      printf("[Graphic] %'.4G FPS (%'d frames)\n",
             count*1.0f/elapsed, count);
      count = 0;
      elapsed = 0.0f;
    }
#endif

    window.clear(sf::Color(250, 255, 250));
    manager->draw(window);
    window.display();
  }
}

void runLogic(const WindowStatus* stat, StateManager* manager) {
  sf::Clock clock;
  while (!stat->isOpen) { // Wait for window to open.
    clock.restart(); // needed for optimized compilation
  }

#ifdef DEBUG
  uint_fast64_t count = 0;
  float elapsed = 0.0f;
#endif

  while (stat->isOpen) {
    if (!stat->focused) {
      clock.restart();
      continue;
    }
    const float dt = clock.restart().asSeconds();

#ifdef DEBUG
    elapsed += dt;
    if (++count >= 2E6) {
      printf("[Logic]   %'.4G SPS (%'llu steps)\n",
             count*1.0f/elapsed, count);
      count = 0llu;
      elapsed = 0.0f;
    }
#endif

    manager->update(dt);
  }
  manager->close();
}
