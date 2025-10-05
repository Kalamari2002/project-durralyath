#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>

inline constexpr float c_WINDOW_WIDTH = 1600.0f;
inline constexpr float c_WINDOW_HEIGHT = 900.0f;

inline constexpr unsigned int c_NAME_TAG_FONT_SIZE = 30;

inline const std::filesystem::path c_TEXT_FONT_PATH = "assets/fonts/Quicksand-VariableFont_wght.ttf"; // can't be constexpr cause it's not a literal type
inline const std::filesystem::path c_DEFAULT_PORTRAIT_PATH = "assets/textures/board/default-portrait.jpg";

inline const sf::Color c_DEFAULT_LINE_COLOR(158, 14, 38);
inline const sf::Color c_DEFAULT_BACKGROUND_COLOR(222, 206, 106);
inline const sf::Color c_DEFAULT_WINDOW_BACKGROUND(0, 200, 0);