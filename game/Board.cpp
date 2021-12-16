#include "Board.h"

Board::Board(int sizeX, int sizeY, int bombAmount) : sizeX(sizeX), sizeY(sizeY), bombAmount(bombAmount), end(0) {
  this->board = new Slot*[sizeX * sizeY];

  this->markedAmount = 0;
  this->markedCorrectly = 0;

  for (int x = 0; x < sizeX; x++) {
    for (int y = 0; y < sizeY; y++) {
      this->board[toSlot(x, y)] = new Slot;
      this->board[toSlot(x, y)]->value = EMPTY;
      this->board[toSlot(x, y)]->marked = false;
      this->board[toSlot(x, y)]->highlight = false;
    }
  }

  srand((unsigned)time(NULL));

  for (int i = 0; i < bombAmount; i++) {
    this->board[rand() % (sizeX * sizeY)]->value = BOMB;
  }


}

Board::~Board() {
  for (int i = 0; i < (sizeX * sizeY); i++) delete this->board[i];
  delete[] this->board;
}

int Board::toSlot(unsigned int x, unsigned int y) {
  return x + ((y * sizeX));
}

bool Board::isEmpty(unsigned int slot) {

  if (slot > (sizeX * sizeY) - 1)
    return false;

  if (this->board[slot]->value == BOMB)
    return false;

  return this->board[slot]->value == EMPTY;
}

bool Board::isClickable(unsigned int slot) {

  if (slot > (sizeX * sizeY) - 1)
    return false;

  if (this->board[slot]->value == BOMB)
    return true;

  return this->board[slot]->value == EMPTY;
}

int Board::click(unsigned int slot) {
  if (!isClickable(slot)) return EMPTY;

  if (this->board[slot]->value == BOMB) {
    this->end = 1;
    return BOMB;
  }

  int around = getAround(slot);

  if (around == 0) {
    int topX = (slot % sizeX) - 1;
    int topY = (slot / sizeX) - 1;

    for (int x = 0; x <= 2; x++) {
      for (int y = 0; y <= 2; y++) {
        if (x + topX >= sizeX || x + topX < 0)
          continue;
        if (y + topY >= sizeY || y + topY < 0)
          continue;

        click(toSlot(x + topX, y + topY));
      }
    }
  }

  return around;


}

void Board::rightClick(unsigned int slot) {

  if (!isClickable(slot)) return;

  if (this->board[slot]->marked) {
    this->board[slot]->marked = false;
    this->markedAmount--;
    if (this->board[slot]->value == BOMB) this->markedCorrectly--;
  } else {
    this->board[slot]->marked = true;
    this->markedAmount++;
    if (this->board[slot]->value == BOMB) this->markedCorrectly++;
  }

  if (markedCorrectly == bombAmount && markedAmount == bombAmount) {
    this->end = 2;
  }
}

short Board::getAround(unsigned int slot) {

  if (slot > (sizeX * sizeY) - 1) return EMPTY;

  if (this->board[slot]->value == BOMB) return BOMB;

  short amount = 0;

  int topX = (slot % sizeX) - 1;
  int topY = (slot / sizeX) - 1;

  for (int x = 0; x <= 2; x++) {
    for (int y = 0; y <= 2; y++) {
      if (x + topX >= sizeX || x + topX < 0) continue;
      if (y + topY >= sizeY || y + topY < 0) continue;


      if (this->board[toSlot(x + topX, y + topY)]->value == BOMB)
        amount = amount + 1;
    }
  }

  this->board[slot]->value = amount;

  this->board[slot]->marked = false;

  return amount;
}
