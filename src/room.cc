// room.cc
// Terrance Howard (heyterrance@gmail.com)

#include "room.h"

Room::Room(int i, int j) : x(i), y(j), index( getIndex(i, j) ) {
  dbprintf("Room() %d: (%d, %d)\n", index, x, y);
  loadBlocks();
  load(RoomManager::getFile(index));
}

Room::~Room() {
  for (auto d: drawables) {
    if (d)
      delete d;
    d = nullptr;
  }
}

int Room::getIndex(int i, int j) {
  if (i < 0 or i > kRoomsX-1 or j < 0 or j > kRoomsY-1)
    return -1;
  return j + i * Room::kRoomsY;
}

std::pair<int, int> Room::getPos(int index) {
  int j = index % kRoomsX;
  int i = index / kRoomsX;
  return {i, j};
}

int Room::next(int i, int j) const {
  const int nxt = getIndex(x + i, y + j);
  dbprintf("%d: (%d, %d) -> %d: (%d, %d)\n", index, x, y, nxt, x+i, y+j);
  return (nxt >= 0) ? nxt : index;
}

void Room::addBlock(float left, float top, float width, float height,
                    const sf::Color& color) {
  blocks.push_back(sf::Rect<float>(left, top, width, height));
  sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(width, height));
  rect->setPosition(left, top);
  rect->setFillColor(color);
  sf::RectangleShape* shadow = new sf::RectangleShape(*rect);
  shadow->setPosition(left + 4, top + 4);
  shadow->setFillColor(sf::Color(0, 0, 0, 40));
  drawables.push_back(shadow);
  drawables.push_back(rect);
}

void Room::loadBlocks() {
  // Side borders
  if (x == kRoomsX - 1)
    addBlock(WIN_WIDTH - 4.0f, -20.0f, 4.0f, WIN_HEIGHT + 20.0f, sf::Color::Blue);
  else if (x == 0)
    addBlock(0.0f, -20.0f, 4.0f, WIN_HEIGHT + 20.0f, sf::Color::Blue);
  // Top and bottom borders
  if (y == kRoomsY - 1)
    addBlock(-20.0f, WIN_HEIGHT - 4.0f, WIN_WIDTH + 20.0f, 4.0f, sf::Color::Blue);
  else if (y == 0)
    addBlock(-20.0f, 0.0f, WIN_WIDTH + 20.0f, 4.0f, sf::Color::Blue);
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (auto drawable: drawables)
    target.draw(*drawable, states);
}
  
void Room::load(const std::string& filename) {
  std::ifstream file(filename);
  if (not file) {
    fprintf(stderr, "error: no file %s\n", filename.c_str());
    return;
  } else if (filename.rfind(".room") == std::string::npos) {
		fprintf(stderr, "error: invalid room file %s\n", filename.c_str());
		return;
	}
  std::string line;
  int line_number = 0;
  while (std::getline(file, line) and ++line_number) {
    if (line.length() <= 0) continue;
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if (type == "block") {
      float x, y, w, h;
      if (iss >> x >> y >> w >> h)
        addBlock(x, y, w, h);
      else
        fprintf(stderr, "%s(%d): error: unexpected parameter(s)\n\t%s\n",
            filename.c_str(), line_number, line.c_str());
      continue;
    } else if (type == "//") {
      continue;
    } else {
      fprintf(stderr, "%s(%d): error: unexpected type \"%s\"\n",
          filename.c_str(), line_number, type.c_str());
    }
  }
}
  
void Room::save() const {
}
