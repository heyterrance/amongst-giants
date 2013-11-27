// resources.cc
// Terrance Howard (heyterrance@gmail.com)

#include "resources.h"

// ----------------------------------------------------------------------------
// Paths
// ----------------------------------------------------------------------------

// FontManager paths
std::string FontManager::fontPath_("share/fonts/");
std::unordered_map<std::string, std::string> FontManager::paths_ = {
  {"arial", "arial.ttf"},
  {"arial bold", "arial-bold.ttf"},
};

// TextureManager paths
std::string TextureManager::imagePath_("share/images/");
std::unordered_map<std::string, std::string> TextureManager::paths_ = {
  {"jack-walk", "jack_walk.png"},
  {"jack-walk-shadow", "jack_walk_shadow.png"},
};

// RoomManager paths
std::string RoomManager::roomPath_("share/rooms/");
std::unordered_map<int, std::string> RoomManager::paths_ {
  {1, "room1.room"},
  {3, "room3.room"},
};


// ----------------------------------------------------------------------------
// Implementations
// ----------------------------------------------------------------------------

// FontManager
// ----------------------------------------------------------------------------
std::unordered_map<std::string, sf::Font> FontManager::fonts_;

const sf::Font& FontManager::loadFont(const std::string& name,
                                      const std::string& path) {
  const std::string full_path = fontPath_ + path;
  sf::Font font;
  if ( !font.loadFromFile(full_path) ) {
    dbprintf("[ERROR] Could not load font: %s\n", full_path.c_str());
    exit(404);
  }
  dbprintf("Loaded font: %s\n", full_path.c_str());
  fonts_[name] = font;
  return fonts_[name];
}

void FontManager::setPath(const std::string& path) {
  fontPath_ = path + fontPath_;
}

const sf::Font& FontManager::getFont(const std::string& name) {
  auto it = fonts_.find(name);
  if (it != fonts_.end()) return it->second;
  return loadFont(name, paths_[name]);
}

// TextureManager
// ----------------------------------------------------------------------------
std::unordered_map<std::string, sf::Texture> TextureManager::textures_;

void TextureManager::setPath(const std::string& path) {
  imagePath_ = path + imagePath_;
}

const sf::Texture& TextureManager::loadTexture(const std::string& name,
                                               const std::string& path) {
  const std::string full_path = imagePath_ + path;
  sf::Texture tex;
  if ( !tex.loadFromFile(full_path) ) {
    dbprintf("[ERROR] Could not load texture: %s\n", full_path.c_str());
    exit(404);
  }
  dbprintf("Loaded texture: %s\n", full_path.c_str());
  textures_[name] = tex;
  return textures_[name];
}

const sf::Texture& TextureManager::getTexture(const std::string& name) {
  auto it = textures_.find(name);
  if (it != textures_.end()) return it->second;
  return loadTexture(name, paths_[name]);
}

// RoomManager
// ----------------------------------------------------------------------------
void RoomManager::setPath(const std::string& path) {
  roomPath_ = path + roomPath_;
}

std::string RoomManager::getFile(int index) {
  auto it = paths_.find(index);
  if (it != paths_.end()) return roomPath_ + it->second;
  return "NoRoomFileForIndex.NotARoom";
}
