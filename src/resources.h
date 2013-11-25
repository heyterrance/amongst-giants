// resources.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdio.h> // printf
#include <string> // std::string
#include <unordered_map> // std::unordered_map

#include <SFML/Graphics.hpp> // sf::Font

#include "util.h" // tolower

// FontManager
// Loads and stores fonts
class FontManager {
public:
  // getFont(name)
  // @param std::string name - name of font to get
  // @return sf::Font - font
  static const sf::Font& getFont(const std::string& name);
  static void setPath(const std::string& path);

private:
  // loadFont(name,path)
  // @param std::string name - name of font to load from path_map
  // @param std::string path - 
  // @param bool use_default - whether to use the default path
  // @return sf::Font - font loaded
  static const sf::Font& loadFont(const std::string& name,
                                  const std::string& path);
  
  static std::string fontPath_;
  static std::unordered_map<std::string, sf::Font> fonts_;
  static std::unordered_map<std::string, std::string> paths_;
};

// TextureManager
// Loads and stores textures
class TextureManager {
public:
  static const sf::Texture& getTexture(const std::string& name);

  static void setPath(const std::string& path);

private:
  static const sf::Texture& loadTexture(const std::string& name,
                                        const std::string& path);
 
  static std::string imagePath_;
  static std::unordered_map<std::string, sf::Texture> textures_;
  static std::unordered_map<std::string, std::string> paths_;
  // TODO support different resolution
  // static std::map<std::string, sf::Texture> textures_720p_;
};


// TODO Implement RoomManager for *.room files
// RoomManager
class RoomManager {
public:
  static std::string getFile(int index);

  static void setPath(const std::string& path);

private:
  static std::string roomPath_;
  static std::unordered_map<int, std::string> paths_;
};

#endif
