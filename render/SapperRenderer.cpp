#
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "SapperRenderer.h"

using namespace sf;

SapperRenderer::SapperRenderer(Board* board) : board(board) {
  this->defaultFont.loadFromFile("./fonts/Roboto-Thin.ttf");
  this->window = new RenderWindow(VideoMode(board->sizeX * SQUARE_SIZE + SIDE_BARS, board->sizeY * SQUARE_SIZE + SIDE_BARS + 50), "Sapper", Style::Titlebar | Style::Close);

  while (window->isOpen()) {
    Event event;
    while (window->pollEvent(event)) {
      if (event.type == Event::Closed) {
        window->close();
        break;
      }

      if (board->end == 0) this->event(event);

    }


    this->update();

  }
}

SapperRenderer::~SapperRenderer() {
  delete this->window;
  delete this->board;
}

void SapperRenderer::event(Event &event) {
  switch(event.type) {
   case Event::EventType::MouseButtonPressed: {

     Vector2i m = Mouse::getPosition(*window);
     m.x = m.x - (SIDE_BARS / 2);
     m.y = m.y - (SIDE_BARS / 2) - 50;

     if (m.x < 0 || m.y < 0 || m.x > board->sizeX * SQUARE_SIZE ||
         m.y > board->sizeY * SQUARE_SIZE)
       return;

     m.x = m.x / SQUARE_SIZE;
     m.y = m.y / SQUARE_SIZE;

     if (m.x > this->board->sizeX - 1)
       m.x = this->board->sizeX - 1;
     if (m.y > this->board->sizeY - 1)
       m.y = this->board->sizeY - 1;

     if (Mouse::isButtonPressed(Mouse::Button::Left)) {
       this->board->click(this->board->toSlot(m.x, m.y));
     } else if (Mouse::isButtonPressed(Mouse::Button::Right)) {
       this->board->rightClick(this->board->toSlot(m.x, m.y));
     }

     break;
   }
  }
}

void SapperRenderer::checkMouse() {
  Vector2i m = Mouse::getPosition(*window);
  m.x = m.x - (SIDE_BARS / 2);
  m.y = m.y - (SIDE_BARS / 2) - 50;

  if (m.x < 0 || m.y < 0 || m.x > board->sizeX * SQUARE_SIZE ||
      m.y > board->sizeY * SQUARE_SIZE)
    return;

  m.x = m.x / SQUARE_SIZE;
  m.y = m.y / SQUARE_SIZE;

  if (m.x > this->board->sizeX - 1) m.x = this->board->sizeX - 1;
  if (m.y > this->board->sizeY - 1) m.y = this->board->sizeY - 1;

  this->board->board[this->board->toSlot(m.x, m.y)]->highlight = true;
}

void SapperRenderer::showBox(String s) {
  RectangleShape rec = RectangleShape(Vector2f(this->window->getSize().x - 100, 200));
  rec.setPosition(Vector2f(50, this->window->getSize().y / 2 - 200));
  rec.setFillColor(KNOWN_SLOT_FILL);
  rec.setOutlineColor(KNOWN_SLOT_OUTLINE);
  rec.setOutlineThickness(4);
  window->draw(rec);

  Text text;
  text.setFont(defaultFont);
  text.setCharacterSize(40);
  text.setFillColor(Color(0, 0, 0, 255));

  text.setString(s);
  text.setPosition(rec.getPosition().x + 80, rec.getPosition().y + 40);
  window->draw(text);
}

void SapperRenderer::win() {
  showBox("You've won!");
}
void SapperRenderer::lose() { showBox("You've been exploded to\npiceces..."); }

void SapperRenderer::update() {

  checkMouse();

  window->clear(BACKGROUND_COLOR);

  {
    RectangleShape rec = RectangleShape(Vector2f(board->sizeX * SQUARE_SIZE, board->sizeY * SQUARE_SIZE));
    rec.setPosition(SIDE_BARS / 2, SIDE_BARS / 2 + 50);
    rec.setFillColor(Color(0, 0, 0, 0));
    rec.setOutlineColor(UNKNOWN_HIGHLIGHT);
    rec.setOutlineThickness(2);
    window->draw(rec);
  }

  RectangleShape rec = RectangleShape(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
  rec.setOutlineThickness(-2);

  RectangleShape flag = RectangleShape(Vector2f(SQUARE_SIZE - 8, SQUARE_SIZE - 8));
  flag.setFillColor(Color(255, 0, 0, 255));

  Text text;
  text.setFont(defaultFont);
  text.setCharacterSize(30);
  text.setFillColor(Color(0, 0, 0, 255));

  for (int x = 0; x < this->board->sizeX; x++) {
    for (int y = 0; y < this->board->sizeY; y++) {
      short val = this->board->board[this->board->toSlot(x, y)]->value;

      rec.setPosition(Vector2f(x * SQUARE_SIZE + (SIDE_BARS / 2), y * SQUARE_SIZE + (SIDE_BARS) / 2 + 50));

      if (val != BOMB && val != EMPTY) {

        rec.setFillColor(KNOWN_SLOT_FILL);
        rec.setOutlineColor(KNOWN_SLOT_OUTLINE);
      } else {

        if (this->board->board[this->board->toSlot(x, y)]->highlight) {
          this->board->board[this->board->toSlot(x, y)]->highlight = false;

          rec.setFillColor(UNKNOWN_HIGHLIGHT);
          rec.setOutlineColor(UNKNOWN_HIGHLIGHT_OUTLINE);
        } else {
          rec.setFillColor(UNKNOWN_SLOT_FILL);
          rec.setOutlineColor(UNKNOWN_SLOT_OUTLINE);
        }

      }

      window->draw(rec);

      if ((val == BOMB || val == EMPTY) && this->board->board[this->board->toSlot(x, y)]->marked) {
        flag.setPosition(rec.getPosition().x + 4, rec.getPosition().y + 4);
        window->draw(flag);
      } else if (val != BOMB && val != EMPTY && val != 0) {

        char *str = new char[2];
        sprintf(str, "%d", val);

        text.setString(str);

        delete[] str;

        text.setPosition(rec.getPosition().x + 6,
                         rec.getPosition().y - 4);

        window->draw(text);
      }

    }
  }

  if (board->end == 1) {
    lose();
  } else if (board->end == 2) {
    win();
  }


  window->display();
  window->setView(window->getDefaultView());
}
