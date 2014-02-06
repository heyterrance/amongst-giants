// world_state.cc
// Terrance Howard (heyterrance@gmail.com)

#include "world_state.h"

WorldState::WorldState() : GameState(), jack_(300.0f, 30.0f),
                           room_idx_(Room::getIndex(1,0)), grav_(298.0f) {
  for (int i = 0; i < Room::kRoomsX; ++i) {
    for (int j = 0; j < Room::kRoomsY; ++j) {
      rooms_.push_back(nullptr);
      dbprintf("%d: (%d, %d)\n", Room::getIndex(i, j), i, j);
    }
  }
  loadRoom(room_idx_);
}

WorldState::~WorldState() {
  for (size_t i = 0; i < rooms_.size(); ++i)
    if (rooms_[i])
      delete rooms_[i];
}

void WorldState::refresh() {
  Room* old = rooms_[room_idx_];
  rooms_[room_idx_] = new Room(old->x, old->y);
  delete old;
}

void WorldState::loadRoom(int index, bool load_adjacent) {
  const std::pair<int, int> p = Room::getPos(index);
  return loadRoom(p.first, p.second, load_adjacent);
}

void WorldState::loadRoom(int i, int j, bool load_adjacent) {
  const int idx = Room::getIndex(i, j);
  if (idx >= 0 and idx < Room::kRooms and not rooms_[idx]) {
    rooms_[idx] = new Room(i, j);
    if (load_adjacent) loadAdjacent(i, j);
  }
}

void WorldState::loadAdjacent(int index) {
  const std::pair<int, int> p = Room::getPos(index);
  return loadAdjacent(p.first, p.second);
}

void WorldState::loadAdjacent(int i, int j) {
  loadRoom(i-1, j, false);
  loadRoom(i+1, j, false);
  loadRoom(i, j-1, false);
  loadRoom(i, j+1, false);
}

void WorldState::update(float dt) {
  if (dt == 0.0f) return;
  processKeyboard(dt);
  checkCollision(dt);
  Room* room = rooms_[room_idx_];
  if (room)
		room->update(dt);
  checkRoomBounds(dt);
  jack_.update(dt);
  loadRoom(room_idx_, true);
}

void WorldState::checkCollision(float dt) {
  const Room* room = rooms_[room_idx_];
  if (not room) return;
  jack_.ddy = grav_;

  for (const sf::Rect<float>& block: room->blocks) {
    const auto bound_pair = jack_.fakeUpdate(dt); 
    // Check x collisions
    if ( bound_pair.first.intersects(block) ) {
      if (jack_.dx < 0.0f) jack_.x = block.left + block.width;
      else if (jack_.dx > 0.0f) jack_.x = block.left - jack_.width();
      jack_.dx = 0.0f;
    }

    // Check y collisions
    if ( bound_pair.second.intersects(block) ) {
      if (jack_.dy < 0.0f) { // going up
        jack_.y = block.top + block.height;
        jack_.grounded = false;
      } else if (jack_.dy > 0.0f) { // going down
        jack_.y = block.top - jack_.height() - 0.1f;;
        jack_.grounded = true;
        jack_.ddy = 0.0f;
      }
      jack_.dy = 0.0f;
    }
  }
  const auto& jbounds = jack_.bounds();
  bool in_water = false;
  for (const Water& w : room->waters) {
    if ( jbounds.intersects( w.bounds() ) ) {
      in_water = true;
      break;
    }
  }
  if (in_water) {
    jack_.walk_vel = 55.0f;
    grav_ = 328.0f;
  } else {
    jack_.walk_vel = 94.0f;
    grav_ = 298.0f;
  }
}

bool WorldState::groundBelow(float dt) {
  if (jack_.dy < 0.0f) return false;
  const Room* room = rooms_[room_idx_];
  const float old_ddy = jack_.ddy;
  jack_.ddy = grav_;
  
  
  for (const sf::Rect<float>& block: room->blocks) {
    const auto bound_pair = jack_.fakeUpdateY(dt); 
    if ( bound_pair.second.intersects(block) ) {
      jack_.ddy = old_ddy;
      return true;
    }
  }
  jack_.ddy = old_ddy;
  return false;
  
}

void WorldState::processKeyboard(float dt) {
  moveJack(dt);
}

void WorldState::checkRoomBounds(float dt) {
  const float x1 = jack_.x + jack_.dx * dt;
  if (x1 + jack_.width() > WIN_WIDTH) {
    const int next_idx = rooms_[room_idx_]->next(+1, 0);
    if (next_idx != room_idx_) {
      room_idx_ = next_idx;
      jack_.x = 0;
    }
  } else if (x1 < 0) {
    const int next_idx = rooms_[room_idx_]->next(-1, 0);
    if (next_idx != room_idx_) {
      room_idx_ = next_idx;
      jack_.x = WIN_WIDTH - jack_.width();
    }
  }
  
  const float y1 = jack_.y + jack_.dy * dt;
  if (y1 + jack_.height() > WIN_HEIGHT) { // at the bottom
    const int next_idx = rooms_[room_idx_]->next(0, +1);
    if (next_idx != room_idx_) {
      room_idx_ = next_idx;
      jack_.y = 0.0f;
    }
  } else if (y1 < 0) { // at the top
    const int next_idx = rooms_[room_idx_]->next(0, -1);
    if (next_idx != room_idx_) {
      room_idx_ = next_idx;
      jack_.y = WIN_HEIGHT - jack_.height();
    }
  }
}

void WorldState::moveJack(float dt) {
  // Press Left or Right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or
      sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    jack_.dx = -jack_.walk_vel;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or
             sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    jack_.dx = jack_.walk_vel;

  // Press Up or Down
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or
      sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    if (groundBelow(dt)) {
      jack_.dy = -jack_.jump_vel;
      jack_.grounded = false;
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or
             sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    jack_.dy = 2 * jack_.jump_vel;
  }
}

void WorldState::draw(sf::RenderWindow& window) const {
  const Room* r = rooms_[room_idx_];
  if (not r) return;

  window.draw(jack_);
  for (const auto& w : r->waters)
    window.draw(w);
  window.draw(*r);
}
  
void WorldState::save() {
  for (Room* room : rooms_)
    if(room) room->save();
}
