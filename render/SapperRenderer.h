#include "../game/Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <stdlib.h>
#include <stdio.h>

#define BACKGROUND_COLOR Color(191, 191, 191, 255)

#define UNKNOWN_SLOT_FILL Color(0, 110, 18, 255)
#define UNKNOWN_SLOT_OUTLINE Color(0, 60, 8, 255)

#define UNKNOWN_HIGHLIGHT Color(0, 148, 24, 255)
#define UNKNOWN_HIGHLIGHT_OUTLINE Color(0, 105, 17, 255)

#define KNOWN_SLOT_FILL Color(150, 150, 150, 255)
#define KNOWN_SLOT_OUTLINE Color(60, 60, 60, 255)

#define SQUARE_SIZE 30
#define SIDE_BARS 50

class SapperRenderer {

public:
  Board* board;

  sf::RenderWindow* window;

  sf::Font defaultFont;

  SapperRenderer(Board *board);

  ~SapperRenderer();

  void update();

  void win();
  void lose();

  void checkMouse();

  void showBox(sf::String s);

  void event(sf::Event &event);
};
